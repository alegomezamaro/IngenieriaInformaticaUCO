# GTest include code for fetch content over the internet
include(FetchContent)
FetchContent_Declare(
 googletest
 GIT_REPOSITORY https://github.com/google/googletest.git
 GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main gmock_main)
# End GTest include code
# Testing person library
add_executable(person-test person-test.cc)
target_link_libraries(person-test
PRIVATE GTest::GTest person)
add_test(person-gtests person-test)