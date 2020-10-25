#pragma once
#include "Writefile.h"
#include "Workflow.h"
#include "Factory.h"
#include <string>

Workflow* createWritefile() {
	return new Writefile;
}

static bool add_creatorWritefile()
{
	Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->addCreator("writefile", createWritefile);
	return true;
}
static bool a = add_creatorWritefile();

void Writefile::execute(std::vector<std::string> args)
{
	if (args.size() - 1 != args_num)
		throw std::invalid_argument("Wrong number of arguments Readfile");
	std::ofstream fout(args[1]);
	if (!fout.is_open())
		throw std::invalid_argument("file is not open in Readfile");
	fout << input_text;
}
