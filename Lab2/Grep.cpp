#pragma once
#include "Workflow.h"
#include "Grep.h"
#include "Factory.h"
#include <string>
#include <stdexcept>
#include <iostream>

Workflow* createGrep() {
	return new Grep;
}

static bool add_creatorGrep()
{
	Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->addCreator("grep", createGrep);
	return true;
}
static bool a = add_creatorGrep();

void Grep::execute(std::vector<std::string> args)
{
	if (args.size() - 1 != args_num)
		throw std::invalid_argument("Wrong number of arguments Replace");
	size_t bf = 0; // find begin position
	size_t ef = input_text.find('\n'); // end find fosition
	size_t len = input_text.length();
	while (bf != len)
	{
		std::string substr = input_text.substr(bf, ef - bf);
		if (substr.find(args[1]) != std::string::npos)
		{
			std::cout << substr << std::endl;
		}
		bf = ef + 1;
		ef = input_text.find('\n', bf);
	}
}