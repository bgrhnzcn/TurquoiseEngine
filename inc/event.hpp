#ifndef EVENT_HPP
#define EVENT_HPP

#include "key_event.hpp"
#include <variant>

using Event = std::variant< KeyEvent >;

#endif // !EVENT_HPP
