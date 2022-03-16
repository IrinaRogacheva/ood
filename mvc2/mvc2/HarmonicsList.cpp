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

sig::connection CHarmonicsList::DoOnCurrentIndexChanged(const HarmonicsChangeSignal::slot_type& handler)
{
	return m_currentIndexChanged.connect(handler);
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
	SetCurrentIndex(GetHarmonicsCount() - 1);
}

void CHarmonicsList::DeleteHarmonic(size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("Index is out of range");
	}
	if (m_currentIndex == 0 && GetHarmonicsCount() > 1)
	{
		m_harmonics.erase(m_harmonics.begin() + index);
		m_harmonicDeleted();
		SetCurrentIndex(0);
	}
	else
	{
		m_harmonics.erase(m_harmonics.begin() + index);
		m_harmonicDeleted();
		if (index > 0)
		{
			SetCurrentIndex(index - 1);
		}
	}
}

size_t CHarmonicsList::GetCurrentIndex() const
{
	return m_currentIndex;
}

void CHarmonicsList::SetCurrentIndex(size_t index)
{
	m_currentIndex = index;
	m_currentIndexChanged();
}

GraphPoints CHarmonicsList::CalculateGraphPoints() const
{
	GraphPoints points;
	double n = -10;
	for (size_t i = 0; i <= 200; i++)
	{
		points.x.push_back(n);
		points.y.push_back(0);
		for (auto const harmonic : m_harmonics)
		{
			if (harmonic->GetFunctionType() == HarmonicFunctionType::SIN)
			{
				points.y[i] += harmonic->GetAmplitude() * sin(harmonic->GetFrequency() * n + harmonic->GetPhase());
			}
			else
			{
				points.y[i] += harmonic->GetAmplitude() * cos(harmonic->GetFrequency() * n + harmonic->GetPhase());
			}
		}
		n += 0.1;
	}
	return points;
}
