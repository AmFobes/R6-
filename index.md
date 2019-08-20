---
layout: default
title: Home
nav_order: 1
description: "R6pp is an easy C++ interface for rainbow six siege"
permalink: /
---

# Adding R6pp to your project

### Thirdparty 

R6pp is built using [RapidJSON](https://github.com/Tencent/rapidjson) and [CPR](https://github.com/whoshuu/cpr)
When developing the project I tried to make installation of the dependencies as easy as possible, of course some platforms are not accounted for (Apple for example) so if you encounter any problems just create a [Pull Request](https://github.com/AmFobes/R6pp/compare) if you have a solution or an [Issue](https://github.com/AmFobes/R6pp/issues/new).

If you need any specific build flags / definitions the only ones R6pp modify are 
- _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
- CMAKE_USE_WINSSL (If on windows)
- CMAKE_USE_OPENSSL (If on windows)
- USE_SYSTEM_CURL (If on Linux)
- BUILD_CURL_EXE
- CURL_STATICLIB
- BUILD_CPR_TESTS
- RAPIDJSON_BUILD_EXAMPLES
- RAPIDJSON_BUILD_TESTS

| Flag / Definition                         | Value | Platform | Comment                                 |
|:------------------------------------------|:------|:---------|:----------------------------------------|
| _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING|       | ALL      | See CMakeLists.txt or gtest [Issue](https://github.com/google/googletest/issues/1111)                     
| CMAKE_USE_WINSSL                          | `ON`  | Windows  | CPR on windows doesn't work with OPENSSL                                            
| CMAKE_USE_OPENSSL                         | `OFF` | Windows  | Disable OPENSSL use WINSSL              |
| USE_SYSTEM_CURL                           | `ON`  | Linux    | Running apt is easier than building     |
| BUILD_CURL_EXE                            | `OFF` | ALL      | CURL executable isn't used              |
| CURL_STATICLIB                            | `ON`  | ALL      | Statically link cpr to CURL             | 
| BUILD_CPR_TESTS                           | `OFF` | ALL      | Issues when running tests on windows    |
| RAPIDJSON_BUILD_EXAMPLES                  | `OFF` | ALL      | Possible issues when building examples? |
| RAPIDJSON_BUILD_TESTS                     | `OFF` | ALL      | Issues when running tests on windows    |

## CMake Submodule (Cross-Platform)

# (Recommended)

Possibly the easiest way to implement the project

Create a dependency folder and enter the directory
```bash
$ mkdir deps
$ cd deps
```
Git clone **Make sure you add the --recursive, you need the thirdparty submodules**
```bash
$ git clone https://github.com/AmFobes/R6pp.git --recursive
```
Go back to your main project directory and edit your CMakeLists.txt so it looks something like this
```CMake
cmake_minimum_required (VERSION 3.4)

project(MyProject)

add_subdirectory(deps/R6pp/R6pp) # Add the R6pp Directory so cmake notices the project
include_directories(deps/R6pp/R6pp) # Add the R6pp header directory so R6pp.h is found

add_executable(MyExecutable "main.cpp")
target_link_libraries(MyExecutable R6pp) # Link the R6pp library to your executable / library
```



