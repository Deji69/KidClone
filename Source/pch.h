#pragma once

// C runtime
#include <cassert>
#include <cstdint>					// C++11
// C++ runtime
#include <algorithm>
#include <any>						// C++17
#include <chrono>					// C++11
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <optional>					// C++17
#include <random>					// C++11
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>				// C++17
#include <tuple>					// C++11
#include <unordered_map>			// C++11
#include <unordered_set>			// C++11
#include <variant>					// C++17
#include <vector>

#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
#endif
