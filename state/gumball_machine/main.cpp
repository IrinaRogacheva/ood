#include "MultiGumballMachineWithState.h"
#include "Menu.h"

void FillUp(multi_with_state::IGumballMachine& gumballMachine)
{
	std::string str; 
	getline(std::cin, str); 
	
	std::istringstream iss(str);
	unsigned n;
	iss >> n;

	if (iss.fail())
	{
		std::cout << "Wrong number of balls argument\n";
		return;
	}

	gumballMachine.FillUp(n);
}

int main()
{
	CMenu menu;
	multi_with_state::CGumballMachine gumballMachine(5);

	menu.AddItem("insertQuarter", "Insert quarter", std::bind(&multi_with_state::CGumballMachine::InsertQuarter, &gumballMachine));
	menu.AddItem("ejectQuarter", "Eject quarter", std::bind(&multi_with_state::CGumballMachine::EjectQuarter, &gumballMachine));
	menu.AddItem("turnCrank", "Turn crank", std::bind(&multi_with_state::CGumballMachine::TurnCrank, &gumballMachine));
	menu.AddItem("fillUp", "Fill up <number of balls>", [&] { FillUp(gumballMachine); });
	menu.AddItem("info", "Show info", [&] {std::cout << gumballMachine.ToString(); });

	menu.Run();

	return 0;
}
