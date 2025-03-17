cmake_minimum_required(VERSION 3.14)
project(wordle_data CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Werror
    -Wall
    -Wno-unused-variable
)

# GTest
include(FetchContent)

option(BUILD_GMOCK OFF)
option(INSTALL_GTEST OFF)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
enable_testing()
# GTest

# Protobuf
find_package(Protobuf REQUIRED)

if (NOT Protobuf_FOUND)
    message(FATAL_ERROR "Protobuf lib not found!")
endif()
if(Protobuf_VERBOSE)
  message(STATUS "Using Protocol Buffers ${protobuf_VERSION}")
endif()

set(PROTOS_
    uuid.proto
    enum_the_char_color.proto
    enum_row_result.proto
    request_row_body.proto
    request_new_game_body.proto
    response_row_body.proto
    response_new_game_body.proto
)
list(TRANSFORM PROTOS_ PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/proto/")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/src/generated/")

add_library(${PROJECT_NAME}-generated STATIC ${PROTOS_})
protobuf_generate (
    TARGET ${PROJECT_NAME}-generated
    LANGUAGE cpp
    PROTOC_OUT_DIR  "${CMAKE_CURRENT_BINARY_DIR}/src/generated/"
    OUT_VAR GENERATED_CPP_FILES
    PROTOS ${PROTOS_}
    IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/proto/
)
target_link_libraries(${PROJECT_NAME}-generated PUBLIC ${PROTOBUF_LIBRARY})
message("GENERATED_CPP_FILES = ${GENERATED_CPP_FILES}")
# Protobuf

# unittests
add_executable(${PROJECT_NAME}-test unittests/server_game_test.cpp)
target_link_libraries(${PROJECT_NAME}-test PUBLIC GTest::GTest ${PROJECT_NAME}-generated)
target_compile_features(${PROJECT_NAME}-test PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME}-test PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/src/generated/")
add_test(${PROJECT_NAME}-google-test ${PROJECT_NAME}-test)
# unittests
