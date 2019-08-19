# CMakeList.txt : CMake project for R6++, include source and define
# project specific logic here.
#
project(R6pp)

set (CMAKE_CXX_STANDARD 11)

cmake_minimum_required (VERSION 3.0)

# cpr uses gtest which uses TR1 which throws warnings which throws an error
# https://github.com/google/googletest/issues/1111 <-- Issue discussed here
# https://github.com/Microsoft/DirectXShaderCompiler/commit/ea1bf8d24ceb05883b6e24517f6cbbb117d4a385 <-- Solution from here
# This is only needed if you build the cpr coverage
add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
add_definitions(-DCURL_STATICLIB )

if(WIN32)
set(CMAKE_USE_WINSSL true)
set(CMAKE_USE_OPENSSL false)
endif()

set(GENERATE_COVERAGE OFF)
add_subdirectory("deps/cpr")
set(RAPIDJSON_BUILD_TESTS OFF)
add_subdirectory("deps/rapidjson")

add_library(R6pp R6pp.cpp R6pp.h)

target_link_libraries(R6pp ${CPR_LIBRARIES})

if(WIN32)
target_link_libraries(R6pp ${OPENSSL_LIBRARIES})
endif()


