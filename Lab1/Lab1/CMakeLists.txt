#
cmake_minimum_required (VERSION 3.17)# minimal version cmake for build

set(CMAKE_CXX_STANDARD 20)#	C++ standart
project ("Ternary_System")#	project name
add_executable (Ternary_System "test.cpp" "Trit_set.cpp")

ADD_SUBDIRECTORY (googletest)
include_directories(googletest/googletest/include)

target_link_libraries(Ternary_System gtest gtest_main)