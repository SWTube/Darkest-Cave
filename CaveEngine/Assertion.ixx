module;

#include <cassert>

#include "CoreTypes.h"

export module Assertion;

namespace cave
{
#define PLUS_OVERFLOW_FL(x, y) (assert())
#define PLUS_OVERFLOW_I_32()
}