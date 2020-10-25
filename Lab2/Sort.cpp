#pragma once
#include "Workflow.h"
#include "Sort.h"
#include "Factory.h"
#include <string>
#include <stdexcept>
#include <algorithm>

Workflow* createSort() {
	return new Sort;
}

static bool add_creatorSort()
{
	Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->addCreator("sort", createSort);
	return true;
}
static bool a = add_creatorSort();

void Sort::execute(std::vector<std::string> args)
{
	if (args.size() - 1 != args_num)
		throw std::invalid_argument("Wrong number of arguments Replace");
	std::vector<std::string> arr;
	size_t bf = 0; // find begin position
	size_t ef = input_text.find('\n'); // end find fosition
	size_t len = input_text.length();
	while (bf != len)
	{
		arr.push_back(input_text.substr(bf, ef - bf));
		bf = ef + 1;
		ef = input_text.find('\n', bf);
	}
	std::sort(arr.begin(), arr.end());
	input_text.clear();
	for (auto i = arr.begin(); i != arr.end(); ++i)
	{
		input_text += *i;
		input_text += '\n';
	}
	input_text.erase(input_text.end() - 1);
}