#include <iostream>

#include "CSVParser.h"

int main() {
    setlocale(LC_CTYPE, "rus");
    std::string filename("example.csv");

    CSVParser<std::string, int, double> result(filename, 0, ','); // parser parce the string of <string, int, double> in csv file 

    result.parse();

    for (int i = 0; i < result.getNumberOfLines(); i++) {
        std::cout << result.get()[i];
        std::cout << std::endl;
    }

    return 0;
}