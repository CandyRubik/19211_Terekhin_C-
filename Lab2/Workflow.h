#pragma once
#include <vector>
#include <string>

class Workflow
{
protected:
	static std::string input_text;
public:
	virtual void execute(std::vector<std::string>) = 0;
	virtual ~Workflow() {};
};
typedef Workflow* (*creator_t) ();

//std::string Workflow::input_text = "";