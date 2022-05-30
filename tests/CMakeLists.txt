cmake_minimum_required(VERSION 3.14)
set(TARGET_NAME test_project)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ${TARGET_NAME} test_entity.cpp
)
target_link_libraries(
        ${TARGET_NAME}
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})
