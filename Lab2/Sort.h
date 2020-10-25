#pragma once
#include "Workflow.h"

class Sort : public Workflow
{
	const int args_num = 0;
public:
	void execute(std::vector<std::string>) override;
};
