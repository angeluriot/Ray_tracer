cmake_minimum_required(VERSION 3.10)

# Project
project(Ray_tracer)

# Sources
file(GLOB_RECURSE SOURCES sources/*.cpp libraries/*.cpp)
file(GLOB_RECURSE HEADERS sources/*.hpp sources/*.h libraries/*.hpp libraries/*.h)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# C++ 17
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC sources)
target_include_directories(${PROJECT_NAME} PUBLIC libraries)

# linker flags
add_link_options(-lm -lmingw32 -lgdi32 -luser32 -lkernel32 -ladvapi32 -lshell32 -lgcc -lmoldname -lmingwex -lmsvcrt -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32)

# Set VS properties
if(MSVC)
	target_compile_options(${PROJECT_NAME} PUBLIC "/Zc:__cplusplus")
	set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	set_property(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
