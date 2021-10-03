#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStation/WeatherData.h"

SCENARIO("The observer removes itself from the list of observers")
{
	CWeatherData wd;
	
	CObserverWhoRemovesItself observerWhoRemovesItself(wd, std::cout);
	wd.RegisterObserver(observerWhoRemovesItself, 0);

	wd.SetMeasurements(3, 0.7, 760);
}

SCENARIO("Notification of observers depending on priority")
{
	CWeatherData wd;

	std::stringstream output;
	CDisplay display(output);
	wd.RegisterObserver(display, 3);

	CObserverWhoRemovesItself observerWhoRemovesItself(wd, output);
	wd.RegisterObserver(observerWhoRemovesItself, 2);

	CStatsDisplay statsDisplay(output);
	wd.RegisterObserver(statsDisplay, 1);

	wd.SetMeasurements(3, 0.7, 760);
	REQUIRE(output.str() == "CStatsDisplay\nCObserverWhoRemovesItself\nCDisplay\n");
}