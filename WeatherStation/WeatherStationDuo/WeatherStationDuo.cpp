#include "WeatherData.h"
#include <sstream>

int main()
{
	CWeatherData inWd;
	CWeatherData outWd;

	CDisplay display(inWd, outWd, std::cout);
	inWd.RegisterObserver(display, 3);
	outWd.RegisterObserver(display, 3);

	CStatsDisplay statsDisplay(inWd, outWd, std::cout);
	inWd.RegisterObserver(statsDisplay, 1);
	outWd.RegisterObserver(statsDisplay, 1);

	inWd.SetMeasurements(3, 0.7, 760);
	outWd.SetMeasurements(4, 0.8, 761);

	inWd.SetMeasurements(10, 0.8, 761);
	outWd.SetMeasurements(-10, 0.8, 761);
	return 0;
}