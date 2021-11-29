#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../gumball_machine/MultiGumBallMachineWithState.h"

using namespace multi_with_state;

std::string ToString(const unsigned count, const unsigned numberOfQuarters, const IState* state)
{
    auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
    return (fmt % count % (count != 1 ? "s" : "") % numberOfQuarters % (numberOfQuarters != 1 ? "s" : "") % state->ToString()).str();
}

SCENARIO("testing the gumball machine in 'sold out' state")
{
    GIVEN("the gumball machine with no gums")
    {
        CGumballMachine m(0);
        CSoldOutState soldOutState(m);

        REQUIRE(m.ToString() == ToString(0, 0, &soldOutState));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("You can't insert a quarter, the machine is sold out")
            {
                REQUIRE(m.ToString() == ToString(0, 0, &soldOutState));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("You can't eject, you haven't inserted a quarter yet")
            {
                REQUIRE(m.ToString() == ToString(0, 0, &soldOutState));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("You turned but there's no gumballs")
            {
                REQUIRE(m.ToString() == ToString(0, 0, &soldOutState));
            }
        }

        WHEN("try to fill up")
        {
            m.FillUp(5);

            THEN("gumball machine has 5 gumballs")
            {
                CNoQuarterState noQuarterState(m);
                REQUIRE(m.ToString() == ToString(5, 0, &noQuarterState));
            }
        }

        WHEN("try to fill up but with zero gumballs")
        {
            m.FillUp(0);

            THEN("gumball machine hasn't changed state")
            {
                REQUIRE(m.ToString() == ToString(0, 0, &soldOutState));
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

        REQUIRE(m.ToString() == ToString(3, 0, &noQuarterState));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("the gumball machine switched to the state 'has quarter'")
            {
                CHasQuarterState hasQuarterState(m);
                REQUIRE(m.ToString() == ToString(3, 1, &hasQuarterState));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("You haven't inserted a quarter")
            {
                REQUIRE(m.ToString() == ToString(3, 0, &noQuarterState));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("You turned but there's no quarter")
            {
                REQUIRE(m.ToString() == ToString(3, 0, &noQuarterState));
            }
        }

        WHEN("try to fill up")
        {
            m.FillUp(3);

            THEN("gumball machine has filled up")
            {
                REQUIRE(m.ToString() == ToString(6, 0, &noQuarterState));
            }
        }
    }
}

SCENARIO("testing the gumball machine in 'has quarter' state")
{
    GIVEN("the gumball machine with a few gums and max count of quarters")
    {
        CGumballMachine m(3);
        m.InsertQuarter();
        m.InsertQuarter();
        m.InsertQuarter();
        m.InsertQuarter();
        m.InsertQuarter();

        CHasQuarterState hasQuarterState(m);

        REQUIRE(m.ToString() == ToString(3, 5, &hasQuarterState));

        WHEN("try to insert one more quarter than max")
        {
            m.InsertQuarter();

            THEN("the gumball machine still has 5 quarters")
            {
                REQUIRE(m.ToString() == ToString(3, 5, &hasQuarterState));
            }
        }

        AND_WHEN("press on button 'eject quarter'")
        {
            m.EjectQuarter();

            THEN("all quarters have been ejected")
            {
                CNoQuarterState noQuarterState(m);
                REQUIRE(m.ToString() == ToString(3, 0, &noQuarterState));
            }
        }

        AND_WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("count of gums and count of quarters decreased by one")
            {
                REQUIRE(m.ToString() == ToString(2, 4, &hasQuarterState));

                WHEN("try to insert one more quarter")
                {
                    m.InsertQuarter();

                    THEN("count of quarters has increased by one")
                    {
                        REQUIRE(m.ToString() == ToString(2, 5, &hasQuarterState));
                    }
                }
            }

            WHEN("try to buy two more gums")
            {
                m.TurnCrank();
                m.TurnCrank();

                THEN("the gumball machine switched to the state 'sold out'")
                {
                    CSoldOutState soldOutState(m);
                    REQUIRE(m.ToString() == ToString(0, 2, &soldOutState));

                    WHEN("try to fill up")
                    {
                        m.FillUp(3);

                        THEN("the gumball machine switched to the state 'has quarter'")
                        {
                            REQUIRE(m.ToString() == ToString(3, 0, &hasQuarterState));
                        }
                    }

                    WHEN("try to eject quarter at the state 'sold out'")
                    {
                        m.EjectQuarter();

                        THEN("no quarters left")
                        {
                            REQUIRE(m.ToString() == ToString(0, 0, &soldOutState));
                        }
                    }
                }
            }
        }

        WHEN("try to fill up")
        {
            m.FillUp(3);

            THEN("gumball machine has filled up")
            {
                REQUIRE(m.ToString() == ToString(6, 5, &hasQuarterState));
            }
        }
    }
}