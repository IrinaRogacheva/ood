#include "HarmonicsList.h"
#include <iostream>

CHarmonicsList::CHarmonicsList()
{
	AddHarmonic(std::make_shared<CHarmonic>(1, HarmonicFunctionType::SIN, 1, 0));
}

CHarmonicsList::~CHarmonicsList()
{
}

sig::connection CHarmonicsList::DoOnHarmonicAdded(const HarmonicsChangeSignal::slot_type& handler)
{
	return m_harmonicAdded.connect(handler);
}

sig::connection CHarmonicsList::DoOnHarmonicDeleted(const HarmonicsChangeSignal::slot_type& handler)
{
	return m_harmonicDeleted.connect(handler);
}

size_t CHarmonicsList::GetHarmonicsCount() const
{
	return m_harmonics.size();
}

std::shared_ptr<CHarmonic> CHarmonicsList::GetHarmonicAtIndex(size_t index) const
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_harmonics.at(index);
}

void CHarmonicsList::AddHarmonic(std::shared_ptr<CHarmonic> harmonic)
{
	m_harmonics.push_back(harmonic);
	m_harmonicAdded();
}

void CHarmonicsList::DeleteHarmonic(size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	
	m_harmonics.erase(m_harmonics.begin() + index);
	m_harmonicDeleted();
}

double CHarmonicsList::CalculateFunctionValue(double x) const
{
	double y = 0;

	for (auto const harmonic : m_harmonics)
	{
		if (harmonic->GetFunctionType() == HarmonicFunctionType::SIN)
		{
			y += harmonic->GetAmplitude() * sin(harmonic->GetFrequency() * x + harmonic->GetPhase());
		}
		else
		{
			y += harmonic->GetAmplitude() * cos(harmonic->GetFrequency() * x + harmonic->GetPhase());
		}
	}
	return y;
}
