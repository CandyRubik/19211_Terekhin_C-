#pragma once
#include "Program_parser.h"
#include <fstream>

std::list<std::pair<int, std::vector<std::string>>>& Parser::execute()
{
	return execution_list;
}

Parser::Parser(std::string input, std::string output)
{
	std::ifstream fin("..\\..\\..\\workflow.txt");
	if (!fin.is_open())
	{
		throw std::invalid_argument("File with program have not open!");
	}
	// finding word "csed"
	std::string line;
	bool was_csed = false;
	while (getline(fin, line))
	{
		if (line == "csed")
		{
			was_csed = true;
			break;
		}
	}
	if (!was_csed)
		throw std::invalid_argument("In file wasn't \"csed\"!");
	std::getline(fin, line);
	// start parsing list of state
	size_t len_line = line.length();
	std::string str_num;
	int num;
	std::vector<std::string> args;
	for (size_t i = 0; i <= len_line; i++)
	{
		if (!isspace(line[i]) && line[i] != '-' && line[i] != '>')
		{
			str_num.push_back(line[i]);
		}
		else
		{
			num = std::stoi(str_num);
			execution_list.push_back(std::make_pair(num, args));
			str_num.clear();
			i += 3;
		}
	}
	num = std::stoi(str_num);
	execution_list.push_back(std::make_pair(num, args));
	// start parsing block desc-csed
	fin.seekg(std::ios::beg);
	getline(fin, line);
	if(line != "desc")
		throw std::invalid_argument("In file wasn't \"desc\"!");
	while (getline(fin, line))
	{
		if (line == "csed")
		{
			break;
		}
		// start parsing line 
		str_num = line.substr(0, line.find_first_of(' '));
		num = std::stoi(str_num);
		line.erase(0, line.find_first_of(' ') + 3);

		for (size_t i = 0; line[0]; i++)
		{	
			if (std::isspace(line[i]) || line[i] == '\0') { 
				args.push_back(line.substr(0, i));
				line.erase(0, i + 1);
				i = 0;
			}
		}
		std::list<std::pair<int, std::vector<std::string>>>::iterator il = std::find_if(execution_list.begin(),
			execution_list.end(),
			[&num](std::pair<int, std::vector<std::string>> const& elem) {
				return elem.first == num;
			});
		il->second = args;
		args.clear();
	}
	if (input != "")
	{
		args = {"readfile", input };
		execution_list.push_front(std::make_pair(0, args));
		args.clear();
	}
	if (output != "")
	{
		args = { "writefile", output };
		execution_list.push_back(std::make_pair(execution_list.size(), args));
		args.clear();
	}
}