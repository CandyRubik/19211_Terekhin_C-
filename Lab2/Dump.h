#pragma once
#include <fstream>
#include "Workflow.h"

class Dump : public Workflow
{
	const int args_num = 1;
public:
	void execute(std::vector<std::string>) override;
};
