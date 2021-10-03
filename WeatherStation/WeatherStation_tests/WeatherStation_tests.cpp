#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStation/WeatherData.h"

SCENARIO("The observer removes itself from the list of observers from the Update method")
{
	CWeatherData wd;
	
	CObserverWhoRemovesItself observerWhoRemovesItself(wd);
	wd.RegisterObserver(observerWhoRemovesItself);

	wd.SetMeasurements(3, 0.7, 760);
}
