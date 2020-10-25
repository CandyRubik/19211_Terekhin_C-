#pragma once
#include <vector>
#include <string>
#include <list>

class IParser 
{
public:
	virtual std::list<std::pair<int, std::vector<std::string>>>& execute() = 0;
};

class Parser : public IParser
{
	std::list<std::pair<int, std::vector<std::string>>> execution_list;
public:
	Parser(std::string input, std::string output);
	std::list<std::pair<int, std::vector<std::string>>>& execute() override;
};
