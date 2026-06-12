#ifndef EVENT_HPP
#define EVENT_HPP

#include "core/input/key_event.hpp"
#include <variant>

namespace trq
{

using Event = std::variant< KeyState >;

}

#endif // !EVENT_HPP
