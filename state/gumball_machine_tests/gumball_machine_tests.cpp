#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <boost/format.hpp>
#include "../gumball_machine/GumBallMachineWithState.h"

using namespace with_state;

std::string ToString(const unsigned count, const IState* state)
{
    auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
    return (fmt % count % (count != 1 ? "s" : "") % state->ToString()).str();
}

SCENARIO("testing the gumball machine in 'sold out' state") 
{
    GIVEN("the gumball machine with no gums") 
    {
        CGumballMachine m(0);
        CSoldOutState soldOutState(m);

        REQUIRE(m.ToString() == ToString(0, &soldOutState));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("You can't insert a quarter, the machine is sold out")
            {
                REQUIRE(m.ToString() == ToString(0, &soldOutState));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("You can't eject, you haven't inserted a quarter yet")
            {
                REQUIRE(m.ToString() == ToString(0, &soldOutState));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("You turned but there's no gumballs")
            {
                REQUIRE(m.ToString() == ToString(0, &soldOutState));
            }
        }
    }
}

SCENARIO("testing the gumball machine in 'no quarter' state")
{
    GIVEN("the gumball machine with a few gums")
    {
        CGumballMachine m(3);
        CNoQuarterState noQuarterState(m);

        REQUIRE(m.ToString() == ToString(3, &noQuarterState));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("the gumball machine switched to the state 'has quarter'")
            {
                CHasQuarterState hasQuarterState(m);
                REQUIRE(m.ToString() == ToString(3, &hasQuarterState));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("You haven't inserted a quarter")
            {
                REQUIRE(m.ToString() == ToString(3, &noQuarterState));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("You turned but there's no quarter")
            {
                REQUIRE(m.ToString() == ToString(3, &noQuarterState));
            }
        }
    }
}

SCENARIO("testing the gumball machine in 'has quarter' state")
{
    GIVEN("the gumball machine with a few gums and quarter")
    {
        CGumballMachine m(2);
        m.InsertQuarter();
        CHasQuarterState hasQuarterState(m);

        REQUIRE(m.ToString() == ToString(2, &hasQuarterState));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("You can't insert another quarter")
            {
                REQUIRE(m.ToString() == ToString(2, &hasQuarterState));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("the gumball machine switched to the state 'no quarter'")
            {
                CNoQuarterState noQuarterState(m);
                REQUIRE(m.ToString() == ToString(2, &noQuarterState));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("the gumball machine switched to the state 'no quarter' and count of gums decreased by one")
            {
                CNoQuarterState noQuarterState(m);
                REQUIRE(m.ToString() == ToString(1, &noQuarterState));

                WHEN("try to buy one more gum")
                {
                    m.InsertQuarter();
                    m.TurnCrank();

                    THEN("there are no balls left and the gumball machine switched to the state 'sold out'")
                    {
                        CSoldOutState soldOutState(m);
                        REQUIRE(m.ToString() == ToString(0, &soldOutState));
                    }
                }
            }
        }
    }
}