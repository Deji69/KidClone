set (TARGET_NAME KidCloneTests)

# Configure google-test as a downloadable library
configure_file (CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process (COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if (result)
	message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif ()
execute_process (COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if (result)
	message (FATAL_ERROR "Build step for googletest failed: ${result}")
endif ()

set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory (
	${CMAKE_CURRENT_BINARY_DIR}/googletest-src
	${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	EXCLUDE_FROM_ALL
)

# Include directories
include_directories("${gmock_SOURCE_DIR}/include")   # not included automatically for some reason
include_directories (${CMAKE_SOURCE_DIR})

# Configure executable
add_executable (${TARGET_NAME}
	Main.cpp
	Setup.cpp
	Engine/EventsTest.cpp
	Engine/ImageTest.cpp
	Engine/TextureTest.cpp
)
set_target_properties (${TARGET_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/env"
)
target_link_libraries (${TARGET_NAME}
	KidClone_lib
	gtest
)

# Configure tests
include (GoogleTest)
gtest_discover_tests (${TARGET_NAME})
# Fix for VS 2017 and 2019 Preview being unable to discover tests in Test Explorer when using gtest_discover_tests
add_test (KidCloneTests ${TARGET_NAME})
