﻿# CMakeList.txt: проект CMake для Lab4; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Lab4")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lab4 "Lab4.cpp"  "CSVParser.h" "Printer.h"  )

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
