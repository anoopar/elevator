cmake_minimum_required(VERSION 3.14)
project(Elevator VERSION 0.1.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# include(CTest)
enable_testing()

# add_subdirectory (src)

add_executable(
    elevator_test
    test.cpp

    src/state_machine/state_machine.cpp
)

target_include_directories (elevator_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/state_machine)
target_include_directories (elevator_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/state_machine/states)
target_include_directories (elevator_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/event_mgr)
target_include_directories (elevator_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/request_mgr)

target_link_libraries(
    elevator_test
    gtest_main
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(GoogleTest)
gtest_discover_tests(elevator_test)
