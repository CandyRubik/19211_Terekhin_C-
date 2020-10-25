#pragma once
#include "Dump.h"
#include "Workflow.h"
#include "Factory.h"
#include <string>

Workflow* createDump() {
	return new Dump;
}

static bool add_creatorDump()
{
	Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->addCreator("dump", createDump);
	return true;
}
static bool a = add_creatorDump();

void Dump::execute(std::vector<std::string> args)
{
	if (args.size() - 1 != args_num)
		throw std::invalid_argument("Wrong number of arguments Readfile");
	std::ofstream fout(args[1]);
	if (!fout.is_open())
		throw std::invalid_argument("file is not open in Readfile");
	fout << input_text;
}
