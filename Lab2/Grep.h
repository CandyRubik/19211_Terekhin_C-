#pragma once
#include "Workflow.h"

class Grep : public Workflow
{
	const int args_num = 1;
public:
	void execute(std::vector<std::string>) override;
};
