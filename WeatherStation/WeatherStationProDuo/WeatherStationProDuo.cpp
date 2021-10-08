#include "WeatherData.h"
#include <sstream>

int main()
{
	CInsideWeatherData inWd;
	COutsideWeatherData outWd;

	CDisplay display(outWd);
	inWd.RegisterObserver(display, 3);
	outWd.RegisterObserver(display, 3);

	CStatsDisplay statsDisplay(outWd);
	inWd.RegisterObserver(statsDisplay, 1);
	outWd.RegisterObserver(statsDisplay, 1);

	inWd.SetMeasurements(3, 0.7, 760, 6, 90);
	outWd.SetMeasurements(4, 0.8, 761, 10, 45);

	inWd.SetMeasurements(10, 0.8, 761, 5, 120);
	outWd.SetMeasurements(-10, 0.8, 761, 11, 270);
	return 0;
}