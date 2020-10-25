#pragma once
#include "Program_parser.h"

class Executor
{
    std::list<std::pair<int, std::vector<std::string>>> &short_program;
public:
    Executor(std::list<std::pair<int, std::vector<std::string>>>& short_prog_text) : short_program(short_prog_text) {}
    void execute();
};