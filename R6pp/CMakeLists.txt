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

if(NOT DEFINED CMAKE_USE_OPENSSL AND NOT DEFINED CMAKE_USE_WINSSL AND NOT DEFINED CMAKE_USE_DARWINSSL)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
		message(STATUS "Using WINSSL for CURL")
		set(CMAKE_USE_WINSSL ON CACHE BOOL "")
		set(CMAKE_USE_OPENSSL OFF CACHE BOOL "")
	endif()

	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		message(STATUS "Using OPENSSL for CURL")
		set(CMAKE_USE_OPENSSL ON CACHE BOOL "")
	endif()

	if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		message(STATUS "Using DARWINSSL for CURL")
		set(CMAKE_USE_DARWINSSL ON CACHE BOOL "")
		set(CMAKE_USE_OPENSSL OFF CACHE BOOL "")
	endif()
endif()

if(NOT DEFINED USE_SYSTEM_CURL AND ${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
message(STATUS "Using system CURL for LINUX")
set(USE_SYSTEM_CURL ON CACHE BOOL "")
set(USE_SYSTEM_CURL ON CACHE INTERNAL BOOL "")
endif()

set(BUILD_CURL_EXE OFF CACHE BOOL "")
set(CURL_STATICLIB ON CACHE BOOL "")
set(BUILD_CPR_TESTS OFF CACHE BOOL "")
add_subdirectory("dep/cpr")

set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "")
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory("dep/rapidjson")


add_library(R6pp "src/R6pp.cpp" "include/R6pp/R6pp.h" "include/R6pp/Types.h" "include/R6pp/Operators.h")

target_include_directories(R6pp PUBLIC "include")
target_include_directories(R6pp PUBLIC "dep/rapidjson/include")

target_link_libraries(R6pp ${CPR_LIBRARIES})





