# CMakeList.txt: проект CMake для Lab2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Lab2")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lab2 "main.cpp"  "Workflow.h"  "Program_parser.h" "Program_parser.cpp" "Executor.h" "Executor.cpp" "Factory.h" "ReadFile.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
