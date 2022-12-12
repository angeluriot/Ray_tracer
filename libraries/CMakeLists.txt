# lodepng sources
file(GLOB_RECURSE LODEPNG_SOURCES lodepng/*.cpp lodepng/*.h lodepng/*.hpp)

# yaml sources
file(GLOB_RECURSE YAML_SOURCES yaml/*.cpp yaml/*.h yaml/*.hpp)

# Create library
add_library(Libraries STATIC ${LODEPNG_SOURCES} ${YAML_SOURCES})

# Includes
target_include_directories(Libraries PUBLIC lodepng)
target_include_directories(Libraries PUBLIC yaml)

# linker flags
add_link_options(-lmingw32 -lgdi32 -luser32 -lkernel32 -ladvapi32 -lshell32 -lgcc -lmoldname -lmingwex -lmsvcrt -lwinspool -lcomdlg32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32)

# OpenGL
if (MINGW OR MSVC)
	add_definitions(-DGLEW_STATIC)
	add_subdirectory(GLEW EXCLUDE_FROM_ALL)
	target_link_libraries(Libraries PRIVATE libglew_static)
else()
	find_package(OpenGL REQUIRED)
	find_package(GLEW REQUIRED)
	include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
	target_link_libraries(Libraries PUBLIC OpenGL::OpenGL GLEW::GLEW)
endif()
