#include "FileReader.h"

void FileReader::read(std::ifstream& fin)
{
	std::string line;
	while (std::getline(fin, line))
	{
		long long int i = 0;
		while (line[0]) { // идем по символам
			if (!std::isalnum(line[i]) && !isrussian((unsigned char)line[i])) { // если нашли не буквацифру
				std::string word = line.substr(0, i);
				words[word]++;
				line.erase(0, i + 1);
				i = 0;
				word_counter++;
			}
			i++;
		}
	}
}

void FileReader::write(std::ofstream& fout)
{
	//создаем вектор из map'a
	std::vector< std::pair< std::string, int > > vec(words.begin(), words.end());
	//сортируем этот вектор по значению
	std::sort(vec.begin(), vec.end(), comp);
	//вывод 
	fout.precision(2);
	for (auto p : vec)
		fout << p.first << ',' << p.second << ',' << (double)p.second * 100 / word_counter << '%' << std::endl;
}

bool comp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
{
	return a.second > b.second;
}

bool FileReader::isrussian(unsigned char ch)
{
	return (ch > 191) || (ch == '-') || (ch == '"') ? true : false;
}