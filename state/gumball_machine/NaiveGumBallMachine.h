#pragma once

#include <iostream>
#include <boost/format.hpp>

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CGumballMachine(unsigned count)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter\n";
			AddQuarter();
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			if (m_numberOfQuarters < MAX_NUMBER_OF_QUARTERS)
			{
				std::cout << "You inserted a quarter\n";
				AddQuarter();
			}
			else
			{
				std::cout << "You can't insert more than " << MAX_NUMBER_OF_QUARTERS << " quarters\n";
			}
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			EjectAllQuarters();
			cout << "All quarters returned\n";
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			cout << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			if (m_numberOfQuarters != 0)
			{
				EjectAllQuarters();
				std::cout << "All quarters are ejected\n";
			}
			else
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs\n";
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
			cout << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(unsigned numBalls)
	{
		m_count = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	std::string ToString()const
	{
		std::string state =
			(m_state == State::SoldOut)    ? "sold out" :
			(m_state == State::NoQuarter)  ? "waiting for quarter" :
			(m_state == State::HasQuarter) ? "waiting for turn of crank"
			                               : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % m_numberOfQuarters % (m_numberOfQuarters != 1 ? "s" : "") % state).str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot\n";
			--m_count;
			--m_numberOfQuarters;
			if (m_count == 0)
			{
				cout << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				if (m_numberOfQuarters == 0)
				{
					m_state = State::NoQuarter;
				}
				else
				{
					m_state = State::HasQuarter;
				}
			}
			break;
		case State::NoQuarter:
			cout << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed\n";
			break;
		}
	}

	void AddQuarter()
	{
		m_numberOfQuarters++;
	}

	void EjectAllQuarters()
	{
		m_numberOfQuarters = 0;
	}

	unsigned m_count;
	unsigned m_numberOfQuarters = 0;
	State m_state = State::SoldOut;

	const unsigned MAX_NUMBER_OF_QUARTERS = 5;
};
}