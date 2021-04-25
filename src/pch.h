#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <assert.h>

#define A_LOG_OUT(x) ::std::cout << x << '\n'

# ifdef NDEBUG
#   define ASTRUM_RELEASE
# else
#   define ASTRUM_DEBUG
# endif

# ifdef ASTRUM_RELEASE
#   define A_DEBUG_LOG_OUT(x) ((void)0)
# else
#   define A_DEBUG_LOG_OUT(x) ::std::cout << x << '\n'
# endif

# ifdef ASTRUM_RELEASE
#   define A_ASSERT(x) ((void)0)
# else
#   define A_ASSERT(x) assert(x)
# endif