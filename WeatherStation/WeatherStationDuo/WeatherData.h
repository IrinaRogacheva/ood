#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(const IObservable<SWeatherInfo>& observableIn, const IObservable<SWeatherInfo>& observableOut, std::ostream& output)
		: m_observableIn(observableIn)
		, m_observableOut(observableOut)
		, m_output(output)
	{
	}
private:

	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_observableIn)
		{
			m_output << "Data received from sensors inside\n";
		}
		else if (&observable == &m_observableOut)
		{
			m_output << "Data received from sensors outside\n";
		}

		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	std::ostream& m_output;
	const IObservable<SWeatherInfo>& m_observableIn;
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

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(const IObservable<SWeatherInfo>& observableIn, const IObservable<SWeatherInfo>& observableOut, std::ostream& output)
		: m_temperatureStatistic(CStatisticsUpdater("Temp"))
		, m_observableIn(observableIn)
		, m_observableOut(observableOut)
		, m_humidityStatistic(CStatisticsUpdater("Hum"))
		, m_pressureStatistic(CStatisticsUpdater("Pressure"))
		, m_output(output)
	{
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo> const& observable) override
	{
		if (&observable == &m_observableIn)
		{
			m_output << "Data received from sensors inside\n";
		}
		else if (&observable == &m_observableOut)
		{
			m_output << "Data received from sensors outside\n";
		}

		m_temperatureStatistic.UpdateStatistics(data.temperature);
		m_humidityStatistic.UpdateStatistics(data.humidity);
		m_pressureStatistic.UpdateStatistics(data.pressure);
	}

	CStatisticsUpdater m_temperatureStatistic;
	CStatisticsUpdater m_humidityStatistic;
	CStatisticsUpdater m_pressureStatistic;

	const IObservable<SWeatherInfo>& m_observableIn;
	const IObservable<SWeatherInfo>& m_observableOut;
	std::ostream& m_output;
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
