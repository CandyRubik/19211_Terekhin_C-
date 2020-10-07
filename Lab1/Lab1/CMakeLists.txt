# CMakeList.txt: проект CMake для Lab1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.17)# минимальная версия cmake для сборки

set(CMAKE_CXX_STANDARD 20)#стандарт cpp для компиляции
project ("Ternary_System")#название проекта
add_executable (Ternary_System "test.cpp" "Trit_set.cpp")
################################
# GTest
################################
ADD_SUBDIRECTORY (googletest)
include_directories(googletest/googletest/include)
# Добавьте источник в исполняемый файл этого проекта.
# Link test executable against gtest & gtest_main
target_link_libraries(Ternary_System gtest gtest_main)