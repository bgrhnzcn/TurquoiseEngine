#ifndef KEY_CODE_HPP
#define KEY_CODE_HPP

#include <GLFW/glfw3.h>
#include <cstddef>
#include <string_view>

#define ENUM_LIST                                                              \
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
	X(R)                                                                       \
	X(S)                                                                       \
	X(T)                                                                       \
	X(U)                                                                       \
	X(V)                                                                       \
	X(W)                                                                       \
	X(Q)                                                                       \
	X(Y)                                                                       \
	X(Z)                                                                       \
	X(X)                                                                       \
	X(1)                                                                       \
	X(2)                                                                       \
	X(3)                                                                       \
	X(4)                                                                       \
	X(5)                                                                       \
	X(6)                                                                       \
	X(7)                                                                       \
	X(8)                                                                       \
	X(9)                                                                       \
	X(0)

class KeyCode
{
  public:
	enum class Value;

  public:
	// EXPERIMENTAL
	consteval static auto size() -> std::size_t;
	constexpr auto toString() const -> std::string_view;

  public:
	KeyCode()					  = default;
	KeyCode(const KeyCode& other) = default;
	KeyCode(Value value);

  public:
	operator Value() const;

  private:
	Value value;

  public:
	enum class Value
	{
#define X(name) KEY_##name = GLFW_KEY_##name,
		ENUM_LIST
#undef X
	};
};

consteval auto KeyCode::size() -> std::size_t
{
	constexpr int array[] = {
#define X(name) 0,
		ENUM_LIST
#undef X
	};
	return sizeof(array) / sizeof(int);
}

constexpr auto KeyCode::toString() const -> std::string_view
{
	switch (value)
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

#undef ENUM_LIST

#endif // !KEY_CODE_HPP
