#include "key_code.hpp"

KeyCode::KeyCode(Value value) { this->value = value; }
KeyCode::operator Value() const { return value; }
