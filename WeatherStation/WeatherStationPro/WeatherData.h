#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"
#define _USE_MATH_DEFINES
#include <math.h> 
#include <cmath> 

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	int windDirection = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatisticsUpdater
{
public:
	CStatisticsUpdater(std::string parameterName)
		:m_parameterName(parameterName)
	{
	}
	void UpdateStatistics(double parameter)
	{
		if (m_minParameter > parameter)
		{
			m_minParameter = parameter;
		}
		if (m_maxParameter < parameter)
		{
			m_maxParameter = parameter;
		}
		m_accParameter += parameter;
		++m_countAcc;

		std::cout << "Max " << m_parameterName << " " << m_maxParameter << std::endl;
		std::cout << "Min " << m_parameterName << " " << m_minParameter << std::endl;
		std::cout << "Average " << m_parameterName << " " << (m_accParameter / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_minParameter = std::numeric_limits<double>::infinity();
	double m_maxParameter = -std::numeric_limits<double>::infinity();
	double m_accParameter = 0;
	unsigned m_countAcc = 0;
	std::string m_parameterName;
};

class CWindStatisticsUpdater
{
public:
	void UpdateStatistics(double windSpeed, int windDirection)
	{
		m_sinSum += windSpeed * sin(windDirection);
		m_cosSum += windSpeed * cos(windDirection);
		m_countAcc++;
		
		std::cout << "Average Wind Direction " << 180 / M_PI * atan2(m_sinSum / m_countAcc, m_cosSum / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_sinSum = 0;
	double m_cosSum = 0;
	unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStatistic(CStatisticsUpdater("Temp"))
		, m_humidityStatistic(CStatisticsUpdater("Hum"))
		, m_pressureStatistic(CStatisticsUpdater("Pressure"))
		, m_windSpeedStatistic(CStatisticsUpdater("Wind Speed"))
		, m_windDirectionStatistic(CWindStatisticsUpdater())
	{
	}
private:
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStatistic.UpdateStatistics(data.temperature);
		m_humidityStatistic.UpdateStatistics(data.humidity);
		m_pressureStatistic.UpdateStatistics(data.pressure);
		m_windSpeedStatistic.UpdateStatistics(data.windSpeed);
		m_windDirectionStatistic.UpdateStatistics(data.windSpeed, data.windDirection);
	}

	CStatisticsUpdater m_temperatureStatistic;
	CStatisticsUpdater m_humidityStatistic;
	CStatisticsUpdater m_pressureStatistic;
	CStatisticsUpdater m_windSpeedStatistic;
	CWindStatisticsUpdater m_windDirectionStatistic;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	double GetTemperature()const
	{
		return m_temperature;
	}

	double GetHumidity()const
	{
		return m_humidity;
	}

	double GetPressure()const
	{
		return m_pressure;
	}

	double GetWindSpeed()const
	{
		return m_windSpeed;
	}

	int GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, int windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	int m_windDirection = 0;
};

class CObserverWhoRemovesItself : public IObserver<SWeatherInfo>
{
public:
	CObserverWhoRemovesItself(IObservable<SWeatherInfo>& observable, std::ostream& output)
		: m_observable(observable)
		, m_output(output)
	{
	}
private:
	void Update(SWeatherInfo const& data) override
	{
		m_output << "CObserverWhoRemovesItself\n";

		std::cout << "Display Current Temp and then delete itself " << data.temperature << std::endl;
		std::cout << "Display Current Hum and then delete itself " << data.humidity << std::endl;
		std::cout << "Display Current Pressure and then delete itself " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
		m_observable.RemoveObserver(*this);
	}

	IObservable<SWeatherInfo>& m_observable;
	std::ostream& m_output;
};