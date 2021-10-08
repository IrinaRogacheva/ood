#include "WeatherData.h"
#include <sstream>

int main()
{
	CWeatherData wd;
	
	CDisplay display;
	wd.RegisterObserver(display, 3);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 1);
	
	wd.SetMeasurements(3, 0.7, 760, 6, 90);
	wd.SetMeasurements(10, 0.8, 761, 10, 45);
	return 0;
}