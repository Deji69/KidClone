#pragma once
#include <array>
#include <chrono>
#include <filesystem>
#include <functional>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION

#if defined(_WIN32)
	#define KIDCLONE_SYSTEM_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#elif defined(__APPLE__) && defined(__MACH__)
	
#elif defined(__unix__)
	#if defined(__ANDROID__)
		#define KIDCLONE_SYSTEM_ANDROID
	#elif defined(__linux__)
		#define KIDCLONE_SYSTEM_LINUX
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
		#define KIDCLONE_SYSTEM_FREEBSD
	#elif defined(__OpenBSD__)
		#define KIDCLONE_SYSTEM_OPENBSD
	#else
		#error Unknown UNIX OS
	#endif
#else
	#error Unknown OS
#endif

#if defined(_DEBUG)
	#define KIDCLONE_DEBUG
#endif

#if !defined(KIDCLONE_STATIC)
	#if defined(KIDCLONE_SYSTEM_WINDOWS)
		// Windows compilers need specific (and different) keywords for export and import
		#define KIDCLONE_EXPORT __declspec(dllexport)
		#define KIDCLONE_IMPORT __declspec(dllimport)

		// For Visual C++ compilers, we also need to turn off this annoying C4251 warning
		#ifdef _MSC_VER
			#pragma warning(disable: 4251)
		#endif
	#else // Linux, FreeBSD, Mac OS X
		#if __GNUC__ >= 4
			// GCC 4 has special keywords for showing/hidding symbols,
			// the same keyword is used for both importing and exporting
			#define KIDCLONE_EXPORT __attribute__ ((__visibility__ ("default")))
			#define KIDCLONE_IMPORT __attribute__ ((__visibility__ ("default")))
		#else
			// GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
			#define KIDCLONE_EXPORT
			#define KIDCLONE_IMPORT
		#endif
	#endif
#else
	// Static build doesn't need import/export macros
	#define KIDCLONE_EXPORT
	#define KIDCLONE_IMPORT
#endif
#if defined(KIDCLONE_EXPORTS)
	#define KIDCLONE_API KIDCLONE_EXPORT
#else
	#define KIDCLONE_API KIDCLONE_IMPORT
#endif

#include <Source/Common/Logging.h>
#include <Source/Common/Rect.h>
#include <Source/Common/String.h>
#include <Source/Common/Vector2.h>
#include <Source/Helper/CStringView.h>
#include <Source/Helper/NoCopy.h>

namespace KidClone {
	constexpr auto VERSION_MAJOR = 0;
	constexpr auto VERSION_MINOR = 1;
	constexpr auto VERSION_PATCH = 0;
	template<typename T>
	constexpr double pi = T(3.1415926535897932385l);

	using namespace std::string_literals;
	using namespace std::chrono_literals;
	namespace chrono = std::chrono;
	namespace fs = std::filesystem;

	using uint = unsigned int;
	using int8 = int8_t;
	using uint8 = uint8_t;
	using int16 = int16_t;
	using uint16 = uint16_t;
	using int32 = int32_t;
	using uint32 = uint32_t;

	using std::function;
	using std::list;
	using std::shared_ptr;
	using std::string;
	using std::string_view;
	using std::stringstream;
	using std::unique_ptr;
	using std::variant;
	using std::vector;
	using std::weak_ptr;

	using std::make_shared;
	using std::make_unique;

	auto getTimestamp(const char* format = "%F %T")->string;
}
