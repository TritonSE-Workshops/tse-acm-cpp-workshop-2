cmake_minimum_required (VERSION 2.8)
project(cppworkshop2)

find_package(Threads REQUIRED)

include(cmake/Catch.cmake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB test_sources 
    "test/*.cpp"
)

add_executable(tests ${test_sources})
target_include_directories(tests PRIVATE include)
target_include_directories(tests PRIVATE test_include)
target_link_libraries(tests Threads::Threads)

include(CTest)
catch_discover_tests(tests)
