
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

# use it after including CTest
enable_testing()
include(CTest)
include(Catch)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
set(TEST_BUILD_DIR ${CMAKE_BINARY_DIR}/test/)

file(GLOB_RECURSE
    PROJECT_TEST_FILES
    ${PROJECT_SOURCE_DIR}/test/*.cpp)
target_include_directories(
    ${PROJECT_LIBRARY_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
add_executable(tests ${PROJECT_TEST_FILES})
target_link_libraries(tests PUBLIC RuneEngine)
target_link_libraries(tests PUBLIC Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE ${PROJECT_LIBRARY_NAME})
target_link_sfml_libraries(tests)
target_include_directories(
    tests
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

add_test(NAME project_tests COMMAND tests)
catch_discover_tests(tests)
