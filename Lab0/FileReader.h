#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

bool comp(const std::pair< std::string, int >& a, const std::pair< std::string, int >& b);

class FileReader
{
public:
	FileReader() : word_counter(0) {}
	void read(std::ifstream& fin);
	void write(std::ofstream& fout);
protected:
	bool isrussian(unsigned char ch); 
private:
	size_t word_counter;
	std::map<std::string, size_t> words;
};