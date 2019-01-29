# Set CMake minimum version and CMake policy required by KidCloneCommon module
cmake_minimum_required (VERSION 3.9)

# Set project name
project (KidClone)

# Set options
#option (KIDCLONE_TESTING "Enable tests" OFF)

# Set project version
set (KIDCLONE_VERSION_MAJOR 0)
set (KIDCLONE_VERSION_MINOR 1)

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

# Include CTest
include (CTest)
enable_testing ()

# Include KidCloneCommon.cmake module after setting project name
include (KidCloneCommon)

# Configure KidClone source
add_subdirectory ("Source")

# Configure tests build
#if (${KIDCLONE_TESTING})
	add_subdirectory ("Tests")
#endif()
