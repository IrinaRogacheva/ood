#pragma once
#include <functional>
#include <string>
#include <sstream>
#include <vector>

class CMenu
{
public:
	typedef std::function<void()> Command;
	void AddItem(const std::string& shortcut, const std::string& description, const Command& command);

	void Run();

	void ShowInstructions()const;

	void Exit();

private:
	bool ExecuteCommand(const std::string& command);

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{}

		std::string shortcut;
		std::string description;
		Command command;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
};