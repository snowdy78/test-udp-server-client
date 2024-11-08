cmake_minimum_required(VERSION 3.16)
project(MyProject LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(MY_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(MY_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR})

include(FetchContent)

FetchContent_Declare(RuneEngine
    GIT_REPOSITORY https://github.com/snowdy78/cmake-rune-engine.git
    GIT_TAG 0.1.9)
FetchContent_MakeAvailable(RuneEngine)

file(
    GLOB_RECURSE
    PROJECT_SOURCE_FILES
    ${MY_PROJECT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE
    PROJECT_INCLUDE_FILES
    ${MY_PROJECT_SOURCE_DIR}/include/*.hpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${PROJECT_INCLUDE_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC RuneEngine)

target_include_directories(${PROJECT_NAME} PRIVATE "${MY_PROJECT_SOURCE_DIR}/include")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
    VERBATIM)
endif()
