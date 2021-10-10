#include "WeatherData.h"
#include <sstream>

int main()
{
	CInsideWeatherData inWd;
	COutsideWeatherData outWd;

	CDisplay inDisplay(inWd);
	inWd.RegisterObserver(inDisplay, 3);
	outWd.RegisterObserver(inDisplay, 3);

	CDisplay outDisplay(outWd);
	inWd.RegisterObserver(outDisplay, 3);
	outWd.RegisterObserver(outDisplay, 3);

	CStatsDisplay inStatsDisplay(inWd);
	inWd.RegisterObserver(inStatsDisplay, 1);
	outWd.RegisterObserver(inStatsDisplay, 1);

	CStatsDisplay outStatsDisplay(outWd);
	inWd.RegisterObserver(outStatsDisplay, 1);
	outWd.RegisterObserver(outStatsDisplay, 1);

	inWd.SetMeasurements(3, 0.7, 760);
	outWd.SetMeasurements(4, 0.8, 761, 10, 45);

	inWd.SetMeasurements(10, 0.8, 761);
	outWd.SetMeasurements(-10, 0.8, 761, 11, 270);
	return 0;
}