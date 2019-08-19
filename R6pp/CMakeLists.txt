# CMakeList.txt : CMake project for R6++, include source and define
# project specific logic here.
#
project(R6pp)

set (CMAKE_CXX_STANDARD 11)

cmake_minimum_required (VERSION 3.0)

# cpr uses gtest which uses TR1 which throws warnings which throws an error
# https://github.com/google/googletest/issues/1111 <-- Issue discussed here
# https://github.com/Microsoft/DirectXShaderCompiler/commit/ea1bf8d24ceb05883b6e24517f6cbbb117d4a385 <-- Solution from here
# This is only needed if you build the cpr coverage / tests
add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
add_definitions(-DCURL_STATICLIB )

if(WIN32 AND NOT DEFINED CMAKE_USE_OPENSSL)
message(STATUS "Using WINSSL for CURL")
set(CMAKE_USE_WINSSL true)
set(CMAKE_USE_OPENSSL false)
endif()

if(NOT DEFINED USE_SYSTEM_CURL AND UNIX)
message(STATUS "Using system CURL for UNIX")
set(USE_SYSTEM_CURL ON)
endif()

if(NOT DEFINED BUILD_CPR_TESTS)
set(BUILD_CPR_TESTS OFF)
endif()
add_subdirectory("deps/cpr")

if(NOT DEFINED RAPIDJSON_BUILD_TESTS)
set(RAPIDJSON_BUILD_TESTS OFF)
endif()
add_subdirectory("deps/rapidjson")

add_library(R6pp R6pp.cpp R6pp.h)

target_link_libraries(R6pp ${CPR_LIBRARIES})





