cmake_minimum_required(VERSION 3.14)
project(wordle_json CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -Werror
    -Wall
    -Wno-unused-variable
)

# /// [find_userver]
find_package(userver COMPONENTS core chaotic REQUIRED)
# Note: If userver was added via add_subdirectory(path/to/userver), then
# the userver_setup_environment() should be called here.
# /// [find_userver]

# /// [chaotic]
# cmake
file(GLOB_RECURSE SCHEMAS ${CMAKE_CURRENT_SOURCE_DIR}/schemas/*.yaml)
userver_target_generate_chaotic(${PROJECT_NAME}-chgen
    ARGS
        # Map '/components/schemas/*' JSONSchema types to C++ types in 'samples::hello' namespace
        -n "/components/schemas/([^/]*)/=wordle_json::{0}"
        # Generate serializers for responses
        --generate-serializers
    OUTPUT_DIR
        ${CMAKE_CURRENT_BINARY_DIR}/src
    SCHEMAS
        ${SCHEMAS}
    RELATIVE_TO
        ${CMAKE_CURRENT_SOURCE_DIR}
)
# /// [chaotic]

# /// [enums]
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/enums
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src)
# /// [enums]

# /// [unittests]
add_executable(${PROJECT_NAME}-unittest
	       unittests/server_game_test.cpp)
target_link_libraries(${PROJECT_NAME}-unittest ${PROJECT_NAME}-chgen userver::utest)
target_include_directories(${PROJECT_NAME}-unittest PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/src)
target_compile_features(${PROJECT_NAME}-unittest PUBLIC cxx_std_20)
add_google_tests(${PROJECT_NAME}-unittest)
# /// [unittests]
