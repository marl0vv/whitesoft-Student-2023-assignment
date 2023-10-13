cmake_minimum_required(VERSION 3.0.0)
project(WStest VERSION 0.1.0)

include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${CURLPP_LDFLAGS})

include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)

add_executable(WStest main.cpp json.hpp)
target_link_libraries(WStest ${CURLPP_LDFLAGS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
