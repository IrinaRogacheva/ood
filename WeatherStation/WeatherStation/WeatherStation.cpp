#include "WeatherData.h"
#include <sstream>

int main()
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
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}