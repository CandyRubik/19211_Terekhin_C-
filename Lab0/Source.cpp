#include "FileReader.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");
	if (argc < 3) {
		std::cout << "Not enough arguments!" << std::endl; // выводим, что недостаточно аргументов
	}
	else {
		std::ifstream fin(argv[1], std::ios_base::in);
		std::ofstream fout(argv[2], std::ios_base::out | std::ios_base::trunc);
		if (!fin.is_open())
		{
			std::cout << "Error name of input file!" << std::endl; // выводим, что ввели неправильное имя файла 
		}
		else if (!fout.is_open())
		{
			std::cout << "Error name of output file!" << std::endl; // выводим, что ввели неправильное имя файла 
		}
		else
		{
			FileReader text;
			text.read(fin);
			text.write(fout);
		}
		fin.close();
		fout.close();
	}
	return 0;
}
