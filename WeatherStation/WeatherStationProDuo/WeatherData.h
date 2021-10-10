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
public:
	CDisplay(const IObservable<SWeatherInfo>& observableOut)
		: m_observableOut(observableOut)
	{
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		if (&observable == &m_observableOut)
		{
			std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
			std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}

	const IObservable<SWeatherInfo>& m_observableOut;
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
	CStatsDisplay(const IObservable<SWeatherInfo>& observableOut)
		: m_temperatureStatistic(CStatisticsUpdater("Temp"))
		, m_humidityStatistic(CStatisticsUpdater("Hum"))
		, m_pressureStatistic(CStatisticsUpdater("Pressure"))
		, m_windSpeedStatistic(CStatisticsUpdater("Wind Speed"))
		, m_windDirectionStatistic(CWindStatisticsUpdater())
		, m_observableOut(observableOut)
	{
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_observableOut)
		{
			m_windSpeedStatistic.UpdateStatistics(data.windSpeed);
			m_windDirectionStatistic.UpdateStatistics(data.windSpeed, data.windDirection);
		}
		m_temperatureStatistic.UpdateStatistics(data.temperature);
		m_humidityStatistic.UpdateStatistics(data.humidity);
		m_pressureStatistic.UpdateStatistics(data.pressure);
		
	}

	CStatisticsUpdater m_temperatureStatistic;
	CStatisticsUpdater m_humidityStatistic;
	CStatisticsUpdater m_pressureStatistic;
	CStatisticsUpdater m_windSpeedStatistic;
	CWindStatisticsUpdater m_windDirectionStatistic;

	const IObservable<SWeatherInfo>& m_observableOut;
};

class CInsideWeatherData : public CObservable<SWeatherInfo>
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class COutsideWeatherData : public CObservable<SWeatherInfo>
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