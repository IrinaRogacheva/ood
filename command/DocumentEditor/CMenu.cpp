#include "CMenu.h"

void CMenu::AddItem(const std::string& shortcut, const std::string& description, CommandCaller const& commandCaller)
{
	m_items.emplace_back(shortcut, description, commandCaller);
}

void CMenu::Run()
{
	ShowInstructions();

	std::string command;
	while ((std::cout << ">")
		&& (std::cin >> command)
		&& ExecuteCommand(command))
	{
	}
}

void CMenu::ShowInstructions()const
{
	std::cout << "Commands list:\n";
	for (auto& item : m_items)
	{
		std::cout << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const std::string& command)
{
	m_exit = false;

	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == command;
		});
	if (it != m_items.end())
	{
		it->commandCaller();
	}
	else
	{
		std::cout << "Unknown command\n";
	}

	return !m_exit;
}