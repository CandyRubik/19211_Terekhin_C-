#pragma once
#include "Workflow.h"
#include "Replace.h"
#include "Factory.h"
#include <string>
#include <stdexcept>

Workflow* createReplace() {
	return new Replace;
}

static bool add_creatorReplace()
{
	Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->addCreator("replace", createReplace);
	return true;
}
static bool a = add_creatorReplace();

void Replace::execute(std::vector<std::string> args)
{
	if (args.size() - 1 != args_num)
		throw std::invalid_argument("Wrong number of arguments Replace");
	size_t start_pos = 0;
	while ((start_pos = input_text.find(args[1], start_pos)) != std::string::npos) {
		input_text.replace(start_pos, args[1].length(), args[2]);
		start_pos += args[2].length(); // Handles case where 'to' is a substring of 'from'
	}
}