#include "key_code.hpp"

KeyCode::KeyCode(Value value)
{
	value_ = value;
}

KeyCode::operator Value() const
{
	return value_;
}
