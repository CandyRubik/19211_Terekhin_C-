#pragma once
#include <vector>

class Workflow
{
protected:
	static std::string input_text;
public:
	virtual void execute(std::vector<std::string>) = 0;
	virtual ~Workflow() {};
};
typedef Workflow* (*creator_t) ();
