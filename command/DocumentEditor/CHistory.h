#pragma once
#include "ICommand.h"
#include <vector>
#include <memory>

class CHistory
{
public:
	bool CanUndo()const;
	bool CanRedo()const;
	void Undo();
	void Redo();
	void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command);

private:
	std::vector<std::unique_ptr<ICommand>> m_commands;
	size_t m_nextCommandIndex = 0;
	const size_t DEPTH_OF_HISTORY = 10;
};