#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <functional>
#include <boost/range/algorithm/find_if.hpp>

#include "ICommand.h"

class CMenu
{
public:
	CMenu(std::istream& istream, std::ostream& ostream);

	typedef std::function<void()> CommandCaller;

	void AddItem(const std::string& shortcut, const std::string& description, CommandCaller const& commandCaller);

	void Run();

	void ShowInstructions()const;

	void Exit();
private:
	bool ExecuteCommand(const std::string& command);

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, CMenu::CommandCaller const& commandCaller)
			: shortcut(shortcut)
			, description(description)
			, commandCaller(commandCaller)
		{}

		std::string shortcut;
		std::string description;
		CommandCaller commandCaller;
	};
	std::vector<Item> m_items;
	bool m_exit = false;
	std::istream& m_istream;
	std::ostream& m_ostream;
};