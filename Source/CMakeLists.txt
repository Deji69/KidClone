set (TARGET_NAME KidClone)

# Include SDL2
include (FindSDL2)
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIR})

# Include directories
include_directories (${CMAKE_SOURCE_DIR})
include_directories (${CMAKE_SOURCE_DIR}/deps/include)

# Define source files
list (APPEND EXCLUDE_PATTERNS Main.cpp)
define_source_files (EXCLUDE_PATTERNS ${EXCLUDE_PATTERNS} GLOB_CPP_PATTERNS *.cpp ${GLOB_OBJC_PATTERN} RECURSE GROUP PCH pch.h)
add_library (${TARGET_NAME}_lib ${CPP_FILES})
set_target_properties (${TARGET_NAME}_lib PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/env"
)
target_link_libraries (${TARGET_NAME}_lib ${SDL2_LIBRARIES} Version.lib Imm32.lib winmm.lib Mincore.lib)

# Configure executable
add_executable (${TARGET_NAME} Main.cpp)
set_target_properties (${TARGET_NAME} PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/env"
)
target_link_libraries (${TARGET_NAME} ${TARGET_NAME}_lib)
