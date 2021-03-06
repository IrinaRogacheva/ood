#pragma once
#include <sstream>

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Unexecute() = 0;

	virtual ~ICommand() = default;
};