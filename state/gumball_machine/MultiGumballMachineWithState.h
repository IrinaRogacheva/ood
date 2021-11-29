#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace multi_with_state
{

	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual void FillUp(const unsigned numBalls) = 0;
		virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		virtual void AddQuarter() = 0;
		virtual void ReduceQuarter() = 0;
		virtual void EjectAllQuarters() = 0;
		virtual unsigned GetBallCount()const = 0;
		virtual unsigned GetQuarterCount()const = 0;
		virtual unsigned GetMaxQuarterCount()const = 0;

		virtual void FillUp(const unsigned numBalls) = 0;
		virtual void AddGum(const unsigned numBalls) = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}
		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			m_gumballMachine.ReduceQuarter();

			if (m_gumballMachine.GetBallCount() == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				if (m_gumballMachine.GetQuarterCount() == 0)
				{
					m_gumballMachine.SetNoQuarterState();
				}
				else
				{
					m_gumballMachine.SetHasQuarterState();
				}
			}
		}
		void FillUp(const unsigned) override
		{
			std::cout << "You can't fill up gumball machine while gumball is delivering\n";
		}
		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			if (m_gumballMachine.GetQuarterCount() != 0)
			{
				m_gumballMachine.EjectAllQuarters();
				std::cout << "All quartes are ejected\n";
			}
			else
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "sold out";
		}
		void FillUp(const unsigned numBalls) override
		{
			m_gumballMachine.AddGum(numBalls);
			if (m_gumballMachine.GetBallCount() != 0)
			{
				if (m_gumballMachine.GetQuarterCount() == 0)
				{
					m_gumballMachine.SetNoQuarterState();
				}
				else
				{
					m_gumballMachine.SetHasQuarterState();
				}
			}
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			if (m_gumballMachine.GetQuarterCount() < m_gumballMachine.GetMaxQuarterCount())
			{
				std::cout << "You inserted a quarter\n";
				m_gumballMachine.AddQuarter();
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				std::cout << "You can't insert more than " << m_gumballMachine.GetMaxQuarterCount() << " quarters\n";
			}
		}
		void EjectQuarter() override
		{
			std::cout << "All quarters returned\n";
			m_gumballMachine.EjectAllQuarters();
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
		void FillUp(const unsigned numBalls) override
		{
			m_gumballMachine.AddGum(numBalls);
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}
		void FillUp(const unsigned numBalls) override
		{
			m_gumballMachine.AddGum(numBalls);
		}
	private:
		IGumballMachine& m_gumballMachine;
	};

	class CGumballMachine : public IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_count(numBalls)
		{
			if (m_count > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		std::string ToString()const
		{
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
			return (fmt % m_count % (m_count != 1 ? "s" : "") % m_numberOfQuarters % (m_numberOfQuarters != 1 ? "s" : "") % m_state->ToString()).str();
		}
		void FillUp(const unsigned numBalls) override
		{
			m_state->FillUp(numBalls);
		}
	private:
		void AddGum(const unsigned numBalls) override
		{
			m_count += numBalls;
		}
		unsigned GetBallCount() const override
		{
			return m_count;
		}
		virtual void ReleaseBall() override
		{
			if (m_count != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_count;
			}
		}
		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}
		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}
		void SetSoldState() override
		{
			m_state = &m_soldState;
		}
		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
		unsigned GetQuarterCount() const override
		{
			return m_numberOfQuarters;
		}
		unsigned GetMaxQuarterCount() const override
		{
			return MAX_NUMBER_OF_QUARTERS;
		}
		void AddQuarter() override
		{
			m_numberOfQuarters++;
		}
		void ReduceQuarter() override
		{
			m_numberOfQuarters--;
		}
		void EjectAllQuarters() override
		{
			m_numberOfQuarters = 0;
		}
	private:
		unsigned m_numberOfQuarters = 0;
		unsigned m_count = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;

		const unsigned MAX_NUMBER_OF_QUARTERS = 5;
	};

}
