#pragma once

#include <string>
#include <vector>
#include <map>

#include <memory>

#include <iostream>

#include <assert.h>
#include <stdexcept>
#include <cstdlib>

#include "util/size.h"

#define A_LOG_OUT(x) ::std::cout << x << '\n'

#ifdef NDEBUG
#   define ASTRUM_RELEASE
#else
#   define ASTRUM_DEBUG
#endif

#define VOID_ASSEMBLY ((void)0)

#ifdef ASTRUM_RELEASE
#   define A_DEBUG_LOG_OUT(x) VOID_ASSEMBLY
#else
#   define A_DEBUG_LOG_OUT(x) A_LOG_OUT(x)
#endif

#ifdef ASTRUM_RELEASE
#   define A_ASSERT(x) VOID_ASSEMBLY
#else
#   define A_ASSERT(x) assert(x)
#endif