#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../gumball_machine/NaiveGumBallMachine.h"

using namespace naive;

std::string ToString(const unsigned count, const unsigned numberOfQuarters, const std::string& state)
{
    auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
    return (fmt % count % (count != 1 ? "s" : "") % numberOfQuarters % (numberOfQuarters != 1 ? "s" : "") % state).str();
}

SCENARIO("testing the gumball machine in 'sold out' state")
{
    GIVEN("the gumball machine with no gums")
    {
        CGumballMachine m(0);

        REQUIRE(m.ToString() == ToString(0, 0, "sold out"));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("You can't insert a quarter, the machine is sold out")
            {
                REQUIRE(m.ToString() == ToString(0, 0, "sold out"));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("You can't eject, you haven't inserted a quarter yet")
            {
                REQUIRE(m.ToString() == ToString(0, 0, "sold out"));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("You turned but there's no gumballs")
            {
                REQUIRE(m.ToString() == ToString(0, 0, "sold out"));
            }
        }
    }
}

SCENARIO("testing the gumball machine in 'no quarter' state")
{
    GIVEN("the gumball machine with a few gums")
    {
        CGumballMachine m(3);

        REQUIRE(m.ToString() == ToString(3, 0, "waiting for quarter"));

        WHEN("try to insert quarter")
        {
            m.InsertQuarter();

            THEN("the gumball machine switched to the state 'has quarter'")
            {
                REQUIRE(m.ToString() == ToString(3, 1, "waiting for turn of crank"));
            }
        }

        WHEN("try to eject quarter")
        {
            m.EjectQuarter();

            THEN("You haven't inserted a quarter")
            {
                REQUIRE(m.ToString() == ToString(3, 0, "waiting for quarter"));
            }
        }

        WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("You turned but there's no quarter")
            {
                REQUIRE(m.ToString() == ToString(3, 0, "waiting for quarter"));
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

        REQUIRE(m.ToString() == ToString(3, 5, "waiting for turn of crank"));

        WHEN("try to insert one more quarter than max")
        {
            m.InsertQuarter();

            THEN("the gumball machine still has 5 quarters")
            {
                REQUIRE(m.ToString() == ToString(3, 5, "waiting for turn of crank"));
            }
        }

        AND_WHEN("press on button 'eject quarter'")
        {
            m.EjectQuarter();

            THEN("all quarters have been ejected")
            {
                REQUIRE(m.ToString() == ToString(3, 0, "waiting for quarter"));
            }
        }

        AND_WHEN("try to turn crank")
        {
            m.TurnCrank();

            THEN("count of gums and count of quarters decreased by one")
            {
                REQUIRE(m.ToString() == ToString(2, 4, "waiting for turn of crank"));

                WHEN("try to insert one more quarter")
                {
                    m.InsertQuarter();

                    THEN("count of quarters has increased by one")
                    {
                        REQUIRE(m.ToString() == ToString(2, 5, "waiting for turn of crank"));
                    }
                }
            }

            WHEN("try to buy two more gums")
            {
                m.TurnCrank();
                m.TurnCrank();

                THEN("the gumball machine switched to the state 'sold out'")
                {
                    REQUIRE(m.ToString() == ToString(0, 2, "sold out"));

                    WHEN("try to eject quarter at the state 'sold out'")
                    {
                        m.EjectQuarter();

                        THEN("no quarters left")
                        {
                            REQUIRE(m.ToString() == ToString(0, 0, "sold out"));
                        }
                    }
                }
            }
        }
    }
}