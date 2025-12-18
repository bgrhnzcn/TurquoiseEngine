#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <cstdint>
#include <format>
#include <iostream>
#include <ostream>
#include <source_location>
#include <string_view>
class Logger
{

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

  public:
	enum LogType
	{
		INFO,
		WARNING,
		ERROR,
		DEBUG
	};

  public:
	template < typename... Args >
	static void log(LogType type, const LogEntry& format, Args&&... args)
	{
		std::string_view label;
		std::ostream& out = (type == ERROR) ? std::cout : std::cerr;
		switch (type)
		{
		case INFO:
			label = "[INFO]";
			break;
		case WARNING:
			label = "[WARNING]";
			break;
		case ERROR:
			label = "[ERROR]";
			break;
		case DEBUG:
			label = "[DEBUG]";
			break;
		}

		std::string formatedStr =
			std::vformat(format.m_format, std::make_format_args(args...));

		std::string_view fileName = format.m_loc.file_name();
		std::uint32_t lineNumber  = format.m_loc.line();

		out << std::format("{} file: {}:{}: {}", label, fileName, lineNumber,
						   formatedStr)
			<< std::endl;
	}

	template < typename... Args >
	static void info(const LogEntry& format, Args&&... args)
	{
		log(INFO, format, args...);
	}

	template < typename... Args >
	static void error(const LogEntry& format, Args&&... args)
	{
		log(ERROR, format, args...);
	}

	template < typename... Args >
	static void debug(const LogEntry& format, Args&&... args)
	{
		log(DEBUG, format, args...);
	}

	template < typename... Args >
	static void warning(const LogEntry& format, Args&&... args)
	{
		log(WARNING, format, args...);
	}
};

#endif
