//
// Created by Sweet Acid on 25.04.2021.
//

#pragma once

#include <pch.h>

#ifdef SNOW_ENABLE_ASSERTS
#define SNOW_ASSERT(x, ...) { if (!(x)) { SNOW_ERROR("Assertion failed: {0}", ## __VA_ARGS__); raise(SIGTRAP); } }
#define SNOW_CORE_ASSERT(x, ...) { if (!(x)) { SNOW_CORE_ERROR("Assertion failed: {0}", ## __VA_ARGS__); raise(SIGTRAP); } }
#else
#define SNOW_ASSERT(x, ...)
#define SNOW_CORE_ASSERT(x, ...)
#endif
