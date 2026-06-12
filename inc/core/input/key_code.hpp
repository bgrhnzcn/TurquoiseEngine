#ifndef KEY_CODE_HPP
#define KEY_CODE_HPP

#include <GLFW/glfw3.h>
#include <cstddef>
#include <optional>
#include <string_view>

#define ENUM_LIST                                                              \
	X(SPACE)                                                                   \
	X(APOSTROPHE)                                                              \
	X(COMMA)                                                                   \
	X(MINUS)                                                                   \
	X(PERIOD)                                                                  \
	X(SLASH)                                                                   \
	X(0)                                                                       \
	X(1)                                                                       \
	X(2)                                                                       \
	X(3)                                                                       \
	X(4)                                                                       \
	X(5)                                                                       \
	X(6)                                                                       \
	X(7)                                                                       \
	X(8)                                                                       \
	X(9)                                                                       \
	X(SEMICOLON)                                                               \
	X(EQUAL)                                                                   \
	X(A)                                                                       \
	X(B)                                                                       \
	X(C)                                                                       \
	X(D)                                                                       \
	X(E)                                                                       \
	X(F)                                                                       \
	X(G)                                                                       \
	X(H)                                                                       \
	X(I)                                                                       \
	X(J)                                                                       \
	X(K)                                                                       \
	X(L)                                                                       \
	X(M)                                                                       \
	X(N)                                                                       \
	X(O)                                                                       \
	X(P)                                                                       \
	X(Q)                                                                       \
	X(R)                                                                       \
	X(S)                                                                       \
	X(T)                                                                       \
	X(U)                                                                       \
	X(V)                                                                       \
	X(W)                                                                       \
	X(X)                                                                       \
	X(Y)                                                                       \
	X(Z)                                                                       \
	X(LEFT_BRACKET)                                                            \
	X(BACKSLASH)                                                               \
	X(RIGHT_BRACKET)                                                           \
	X(GRAVE_ACCENT)                                                            \
	X(WORLD_1)                                                                 \
	X(WORLD_2)                                                                 \
	X(ESCAPE)                                                                  \
	X(ENTER)                                                                   \
	X(TAB)                                                                     \
	X(BACKSPACE)                                                               \
	X(INSERT)                                                                  \
	X(DELETE)                                                                  \
	X(RIGHT)                                                                   \
	X(LEFT)                                                                    \
	X(DOWN)                                                                    \
	X(UP)                                                                      \
	X(PAGE_UP)                                                                 \
	X(PAGE_DOWN)                                                               \
	X(HOME)                                                                    \
	X(END)                                                                     \
	X(CAPS_LOCK)                                                               \
	X(SCROLL_LOCK)                                                             \
	X(NUM_LOCK)                                                                \
	X(PRINT_SCREEN)                                                            \
	X(PAUSE)                                                                   \
	X(F1)                                                                      \
	X(F2)                                                                      \
	X(F3)                                                                      \
	X(F4)                                                                      \
	X(F5)                                                                      \
	X(F6)                                                                      \
	X(F7)                                                                      \
	X(F8)                                                                      \
	X(F9)                                                                      \
	X(F10)                                                                     \
	X(F11)                                                                     \
	X(F12)                                                                     \
	X(F13)                                                                     \
	X(F14)                                                                     \
	X(F15)                                                                     \
	X(F16)                                                                     \
	X(F17)                                                                     \
	X(F18)                                                                     \
	X(F19)                                                                     \
	X(F20)                                                                     \
	X(F21)                                                                     \
	X(F22)                                                                     \
	X(F23)                                                                     \
	X(F24)                                                                     \
	X(F25)                                                                     \
	X(KP_0)                                                                    \
	X(KP_1)                                                                    \
	X(KP_2)                                                                    \
	X(KP_3)                                                                    \
	X(KP_4)                                                                    \
	X(KP_5)                                                                    \
	X(KP_6)                                                                    \
	X(KP_7)                                                                    \
	X(KP_8)                                                                    \
	X(KP_9)                                                                    \
	X(KP_DECIMAL)                                                              \
	X(KP_DIVIDE)                                                               \
	X(KP_MULTIPLY)                                                             \
	X(KP_SUBTRACT)                                                             \
	X(KP_ADD)                                                                  \
	X(KP_ENTER)                                                                \
	X(KP_EQUAL)                                                                \
	X(LEFT_SHIFT)                                                              \
	X(LEFT_CONTROL)                                                            \
	X(LEFT_ALT)                                                                \
	X(LEFT_SUPER)                                                              \
	X(RIGHT_SHIFT)                                                             \
	X(RIGHT_CONTROL)                                                           \
	X(RIGHT_ALT)                                                               \
	X(RIGHT_SUPER)                                                             \
	X(MENU)

namespace trq
{

class KeyCode
{
  public:
	enum Value
	{
#define X(name) KEY_##name = GLFW_KEY_##name,
		ENUM_LIST
#undef X
	};

  public:
	// EXPERIMENTAL
	consteval static auto size() -> std::size_t;
	constexpr auto toString() const -> std::string_view;
	constexpr static auto fromKeycode(int keycode) -> std::optional< KeyCode >;
	constexpr auto getValue() const -> Value;

  public:
	KeyCode()					  = default;
	KeyCode(const KeyCode& other) = default;
	KeyCode(Value value);

  public:
	operator Value() const;

  private:
	Value value_;
};

consteval auto KeyCode::size() -> std::size_t
{
	return 0
#define X(name) +1
		ENUM_LIST
#undef X
		;
}

constexpr auto KeyCode::toString() const -> std::string_view
{
	switch (value_)
	{
#define X(name)                                                                \
	case KeyCode::Value::KEY_##name:                                           \
		return #name;
		ENUM_LIST
#undef X
	default:
		return "Unknown.";
	}
}

constexpr auto KeyCode::fromKeycode(int keycode) -> std::optional< KeyCode >
{
	switch (keycode)
	{
#define X(name) case Value::KEY_##name:
		ENUM_LIST
		return Value(keycode);
#undef X
	default:
		return std::nullopt;
	}
	return Value(keycode);
}

constexpr auto KeyCode::getValue() const -> Value
{
	return value_;
}

} // namespace trq

#undef ENUM_LIST

#endif // !KEY_CODE_HPP
