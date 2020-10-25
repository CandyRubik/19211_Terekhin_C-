#include <iostream>
#include "Executor.h"

int main(int argc, char **argv)
{

    std::string input = "", output = "";

    if (argc > 2)
    {
        for (int i = 1; i < argc; ++i)
        {
            if ("-i" == argv[i])
            {
                input = argv[++i];
            }
            else if ("-o" == argv[i])
            {
                output = argv[++i];
            }
            else
                throw std::invalid_argument("Wrong args from prompt!");
        }
    }
    Parser block(input, output);
    Executor prog(block.execute());
    prog.execute();
	return 0;
}
