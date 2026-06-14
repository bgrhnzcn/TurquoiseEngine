#include "core/input/key_code.hpp"

namespace trq
{

KeyCode::KeyCode(Value value)
{
	value_ = value;
}

KeyCode::operator Value() const
{
	return value_;
}

} // namespace trq
