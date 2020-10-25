#pragma once
#include "Executor.h"
#include <memory>
#include "Factory.h"
#include "Workflow.h"

void Executor::execute()
{
	for (auto i = short_program.begin(); i != short_program.end(); ++i)
	{
		std::unique_ptr<Workflow> u(Factory<Workflow, std::string, Workflow* (*)()>::getInstance()->makeBlock(i->second[0]));
		u->execute(i->second);
	}
}
