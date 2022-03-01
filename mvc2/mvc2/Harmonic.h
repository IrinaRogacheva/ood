#pragma once
#include "HarmonicFunctionType.h"
#include "Signals.h"

class CHarmonic
{
public:
	CHarmonic(double amplitude, HarmonicFunctionType type, double frequency, double phase);
	using HarmonicChangeSignal = sig::signal<void()>;
	sig::connection DoOnHarmonicChanged(const HarmonicChangeSignal::slot_type& handler);
	HarmonicFunctionType GetFunctionType() const;
	void SetFunctionType(HarmonicFunctionType type);
	double GetAmplitude() const;
	void SetAmplitude(double amplitude);
	double GetFrequency() const;
	void SetFrequency(double frequency);
	double GetPhase() const;
	void SetPhase(double phase);
private:
	HarmonicFunctionType m_functionType = HarmonicFunctionType::SIN;
	double m_amplitude = 1;
	double m_frequency = 1;
	double m_phase = 0;

	HarmonicChangeSignal m_harmonicChanged;
};
