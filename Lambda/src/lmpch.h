#pragma once

#include "Lambda/Core/PlatformDetection.h"

#ifdef LM_PLATFORM_WINDOWS
#ifndef NOMINMAX
// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
#define NOMINMAX
#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Lambda/Core/Base.h"

#include "Lambda/Core/Log.h"

#include "Lambda/Debug/Instrumentor.h"

#ifdef LM_PLATFORM_WINDOWS
#include <Windows.h>
#endif
