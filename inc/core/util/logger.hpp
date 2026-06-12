/**
 * Katip is a single header logging library that use std::format with
 * multi-thread suppport. You can create different logger instances for
 * different part of your code and different threads.
 *
 * To use Katip, you must define KATIP_IMPLEMENTATION before including this
 * header on one compilation unit at most.
 *
 * For single thread, just print every output synchronously.
 *
 * For multi-thread, main idea behind Katip is creating thread for logging
 * operations. All the other threads will write their log to queue and wake up
 * logger thread. Logger thread will consume all queued logs and sleep if all
 * logs consumed. Multi-threading must be enabled with define flag
 * KATIP_MULTITHREAD_ENABLE
 *
 * TODO's:
 * - Feature: Implement a better output stream switch. This will be related to
 *   file logging.
 * - Feature: Implement single thread fallback. This will be default value.
 *   Feature: Implement a better std::terminate handle. Don't want to directly
 *   std::set_terminate because it can be overriden by mistake.
 * - Feature: Implement a configurable log format.
 * - Feature: Add more option like "Error logs will terminate program.".
 * - Feature: Add batch logging. This will prevent other threads log to
 *   interfere when user need more log line than one consecutively.
 * - Fix: Add mutex for accessing LoggerMap.
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <atomic>
#include <concepts>
#include <condition_variable>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <source_location>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>

template < typename T >
concept HasToString = requires(const T& a) {
	{ a.toString() } -> std::same_as< std::string >;
};

template < HasToString T >
struct std::formatter< T > : std::formatter< std::string >
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return formatter_.parse(ctx);
	}

	template < typename FormatContext >
	auto format(const T& obj, FormatContext& ctx) const
	{
		return formatter_.format(obj.toString(), ctx);
	}

  private:
	std::formatter< std::string > formatter_;
};

namespace ktp
{

template < typename... >
constexpr bool always_false_v = false;

class Logger
{
  public: // Types
	enum LogType
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

  private: // Types
	using LoggerMap =
		std::unordered_map< std::string, std::unique_ptr< Logger > >;

	struct LogEntry
	{
		std::string_view m_format;
		std::source_location m_loc;

		template < typename T >
		LogEntry(const T& format, const std::source_location& l =
									  std::source_location::current())
			: m_format(format), m_loc(l)
		{
		}
	};

	struct Log
	{
		const std::string log;
		std::ostream* output;
	};

	struct LoggerContext
	{
	  public:
		LoggerContext();
		~LoggerContext();

	  public:
		std::mutex mutex;
		std::queue< Log > logs;
		std::condition_variable cv;
		std::thread loggerThread;
		std::atomic< bool > stopFlag;
	};

  private: // RAII
	explicit Logger(std::string_view name);

  public: // RAII
	~Logger()						 = default;
	Logger(const Logger&)			 = delete;
	Logger(const Logger&&)			 = delete;
	Logger operator=(const Logger&)	 = delete;
	Logger operator=(const Logger&&) = delete;

  private: // Static Private Function
	static auto logHandler() -> void;
	static auto getContext() -> LoggerContext&;
	static auto getLoggerMap() -> LoggerMap&;
	static auto shutdown() -> void;

  public: // Static Functions
	static const Logger& getLogger();
	static const Logger& getLogger(std::string_view name);
	static void setGlobalLogLevel(LogType level);

  private: // Static Variables
	inline static LogType s_logLevel = DEBUG;

  public: // Instance Functions
	auto toString() const -> std::string;
	Logger& setLogLevel(LogType level);
	Logger& setLogFile(const std::filesystem::path& file);
	Logger& setLogConsole();
	Logger& setLogConsole(std::ostream out, std::ostream err);

  private: // Member Variables
	const std::string m_name;
	LogType m_logLevel;
	std::ofstream m_fileStream;
	std::ostream* m_stdOut = &std::cout;
	std::ostream* m_stdErr = &std::cerr;

  public: // Template Functions
	template < typename... Args >
	auto log(LogType type, const LogEntry& format, Args&&... args) const
		-> void;

	template < typename... Args >
	auto info(const LogEntry& format, Args&&... args) const -> void;

	template < typename... Args >
	auto error(const LogEntry& format, Args&&... args) const -> void;

	template < typename... Args >
	auto debug(const LogEntry& format, Args&&... args) const -> void;

	template < typename... Args >
	auto warning(const LogEntry& format, Args&&... args) const -> void;
};

template < typename... Args >
auto Logger::info(const LogEntry& format, Args&&... args) const -> void
{
	log(INFO, format, args...);
}

template < typename... Args >
auto Logger::error(const LogEntry& format, Args&&... args) const -> void
{
	log(ERROR, format, args...);
}

template < typename... Args >
auto Logger::debug(const LogEntry& format, Args&&... args) const -> void
{
	log(DEBUG, format, args...);
}

template < typename... Args >
auto Logger::warning(const LogEntry& format, Args&&... args) const -> void
{
	log(WARNING, format, args...);
}

template < typename... Args >
auto Logger::log(LogType type, const LogEntry& format, Args&&... args) const
	-> void
{

	if constexpr (!(std::is_default_constructible_v<
						std::formatter< std::remove_cvref_t< Args >, char > >
					&& ...))
	{
		static_assert(always_false_v< Args... >,
					  "\nYou failed to use formatter for this type."
					  "\nPlease implement given method to ypur type:"
					  " std::string toString() const;");
	}
	else
	{
		if (type < m_logLevel && type < s_logLevel)
			return;

		std::string_view label;
		std::ostream& out = (type == ERROR) ? *m_stdErr : *m_stdOut;

		switch (type)
		{
		case INFO:
			label = "INFO";
			break;
		case WARNING:
			label = "WARNING";
			break;
		case ERROR:
			label = "ERROR";
			break;
		case DEBUG:
			label = "DEBUG";
			break;
		}

		std::string formatedStr =
			std::vformat(format.m_format, std::make_format_args(args...));
		std::string_view fileName = format.m_loc.file_name();
		std::uint32_t lineNumber  = format.m_loc.line();
		Log log = {.log	   = std::format("[{}][{}][{}] source: {}:{}: {}",
										 "ThreadName", label, m_name, fileName,
										 lineNumber, formatedStr),
				   .output = &out};

		std::lock_guard< std::mutex > lock(getContext().mutex);
		getContext().logs.push(log);
		getContext().cv.notify_one();
	}
}

#ifdef KATIP_IMPLEMENTATION

Logger::Logger(std::string_view name) : m_name(name), m_logLevel(INFO) {}

Logger::LoggerContext::LoggerContext()
{
	loggerThread = std::thread(Logger::logHandler);
}

Logger::LoggerContext::~LoggerContext()
{
	stopFlag = true;
	cv.notify_one();
	if (loggerThread.joinable())
		loggerThread.join();
}

auto Logger::getLogger() -> const Logger& { return getLogger("Global"); }

auto Logger::getLogger(std::string_view name) -> const Logger&
{
	if (!getLoggerMap().contains(name.data()))
		getLoggerMap().emplace(name,
							   std::unique_ptr< Logger >(new Logger(name)));
	return (*getLoggerMap().at(name.data()));
}

auto Logger::setGlobalLogLevel(LogType level) -> void { s_logLevel = level; }

auto Logger::logHandler() -> void
{
	while (true)
	{
		std::queue< Log > localQueue;
		{
			std::unique_lock< std::mutex > lock(getContext().mutex);
			getContext().cv.wait(lock,
								 []()
								 {
									 return getContext().stopFlag
											|| !getContext().logs.empty();
								 });

			if (getContext().stopFlag && getContext().logs.empty())
				break;

			std::swap(localQueue, getContext().logs);
		}
		while (!localQueue.empty())
		{
			Log currentLog = localQueue.front();

			if (currentLog.output)
				std::println(*currentLog.output, "{}", currentLog.log);

			localQueue.pop();
		}
	}
}

auto Logger::getContext() -> Logger::LoggerContext&
{
	static Logger::LoggerContext ctx;
	return ctx;
}

auto Logger::shutdown() -> void
{
	auto& ctx = Logger::getContext();
	{
		std::lock_guard< std::mutex > lock(ctx.mutex);
		ctx.stopFlag = true;
	}
	ctx.cv.notify_one();

	if (ctx.loggerThread.joinable())
		ctx.loggerThread.join();
	getLoggerMap().clear();
}

auto Logger::getLoggerMap() -> LoggerMap&
{
	static LoggerMap loggers;
	return loggers;
}

auto Logger::toString() const -> std::string
{
	return std::format("{{Logger: {}}}", m_name);
}

auto Logger::setLogLevel(LogType level) -> Logger&
{
	m_logLevel = level;
	return *this;
}

auto Logger::setLogFile(const std::filesystem::path& file) -> Logger&
{
	if (m_fileStream.is_open())
		m_fileStream.close();
	m_fileStream.open(file, std::ios::out | std::ios::trunc);
	if (m_fileStream.is_open())
	{
		m_stdOut = &m_fileStream;
		m_stdErr = &m_fileStream;
	}
	return *this;
}

auto Logger::setLogConsole() -> Logger&
{
	if (m_fileStream.is_open())
		m_fileStream.close();
	m_stdOut = &std::cout;
	m_stdErr = &std::cerr;
	return *this;
}

auto Logger::setLogConsole(std::ostream out, std::ostream err) -> Logger&
{
	if (m_fileStream.is_open())
		m_fileStream.close();
	m_stdOut = &out;
	m_stdErr = &err;
	return *this;
}

#endif

} // namespace ktp
#endif
