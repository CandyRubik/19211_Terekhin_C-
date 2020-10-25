#pragma once
#include "ReadFile.h"
#include "Workflow.h"
#include "Factory.h"
#include <string>

Workflow* createReadFile() {
	return new ReadFile;
}

static bool add_creatorReadFile()
{
	Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->addCreator("readfile", createReadFile);
	return true;
}
static bool a = add_creatorReadFile();

void ReadFile::execute(std::vector<std::string> args)
{
	if (args.size() - 1 != args_num)
		throw std::invalid_argument("Wrong number of arguments Readfile");
	std::string temp;
	std::ifstream fin(args[1]);
	if (!fin.is_open())
		throw std::invalid_argument("file is not open in Readfile");
	while (std::getline(fin, temp))
	{
		temp += '\n';
		Workflow::input_text += temp;
	}
}
