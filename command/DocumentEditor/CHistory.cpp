#include "CHistory.h"
#include "ICommand.h"
#include <cassert>
#include <iostream>

bool CHistory::CanUndo() const
{
	return m_nextCommandIndex > 0;
}

bool CHistory::CanRedo() const
{
	return m_nextCommandIndex < m_commands.size();
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_nextCommandIndex--;
		m_commands[m_nextCommandIndex]->Unexecute();
	}
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_nextCommandIndex]->Execute();
		++m_nextCommandIndex;
	}
}

void CHistory::AddAndExecuteCommand(std::unique_ptr<ICommand>&& command)
{
	command->Execute();

	m_commands.erase(m_commands.begin() + m_nextCommandIndex, m_commands.end());
	m_commands.push_back(std::move(command));
	m_nextCommandIndex++;

	if (m_nextCommandIndex == DEPTH_OF_HISTORY + 1)
	{
		m_commands.erase(m_commands.begin());
		m_nextCommandIndex--;
	}
}