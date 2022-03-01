#include "Harmonic.h"

CHarmonic::CHarmonic(double amplitude, HarmonicFunctionType type, double frequency, double phase)
	: m_amplitude(amplitude)
	, m_functionType(type)
	, m_frequency(frequency)
	, m_phase(phase)
{
}

sig::connection CHarmonic::DoOnHarmonicChanged(const HarmonicChangeSignal::slot_type& handler)
{
	return m_harmonicChanged.connect(handler);
}

HarmonicFunctionType CHarmonic::GetFunctionType() const
{
	return m_functionType;
}

void CHarmonic::SetFunctionType(HarmonicFunctionType type)
{
	m_functionType = type;
	m_harmonicChanged();
}

double CHarmonic::GetAmplitude() const
{
	return m_amplitude;
}

void CHarmonic::SetAmplitude(double amplitude)
{
	m_amplitude = amplitude;
	m_harmonicChanged();
}

double CHarmonic::GetFrequency() const
{
	return m_frequency;
}

void CHarmonic::SetFrequency(double frequency)
{
	m_frequency = frequency;
	m_harmonicChanged();
}

double CHarmonic::GetPhase() const
{
	return m_phase;
}

void CHarmonic::SetPhase(double phase)
{
	m_phase = phase;
	m_harmonicChanged();
}
