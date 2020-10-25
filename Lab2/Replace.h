#pragma once
#include "Workflow.h"

class Replace : public Workflow
{
	const int args_num = 2;
public:
	void execute(std::vector<std::string>) override;
};
