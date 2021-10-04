#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../WeatherStationDuo/WeatherData.h"

SCENARIO("Definition of the subject from which the notification was received")
{
	std::stringstream output;

	CWeatherData inWd;
	CWeatherData outWd;

	CDisplay display(inWd, outWd, output);
	inWd.RegisterObserver(display, 3);
	outWd.RegisterObserver(display, 3);

	inWd.SetMeasurements(3, 0.7, 760);
	outWd.SetMeasurements(4, 0.8, 761);
	REQUIRE(output.str() == "Data received from sensors inside\nData received from sensors outside\n");
}