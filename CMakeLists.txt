cmake_minimum_required(VERSION 3.10)

project(apiset)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(SRC_FILES
	src/apiset.cpp)

add_executable(apiset ${SRC_FILES})

if(NOT MSVC)
    target_compile_options(apiset PUBLIC -Wall -Werror=cast-function-type -Wno-expansion-to-defined -Wunused-parameter -Wtype-limits -Wextra -Wconversion)
endif()
