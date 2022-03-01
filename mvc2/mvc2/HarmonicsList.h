#pragma once
#include "Signals.h"
#include <memory>
#include "Harmonic.h"
#include <vector>

class CHarmonicsList
{
public:
	CHarmonicsList();
	~CHarmonicsList();

	using HarmonicsChangeSignal = sig::signal<void()>;
	sig::connection DoOnHarmonicAdded(const HarmonicsChangeSignal::slot_type& handler);
	sig::connection DoOnHarmonicDeleted(const HarmonicsChangeSignal::slot_type& handler);
	sig::connection DoOnCurrentIndexChanged(const HarmonicsChangeSignal::slot_type& handler);

	size_t GetHarmonicsCount()const;
	std::shared_ptr<CHarmonic> GetHarmonicAtIndex(size_t index)const;
	void AddHarmonic(std::shared_ptr<CHarmonic> harmonic);
	void DeleteHarmonic(size_t index);
	size_t GetCurrentIndex() const;
	void SetCurrentIndex(size_t index);
private:
	size_t m_currentIndex = 0;
	std::vector<std::shared_ptr<CHarmonic>> m_harmonics{};
	HarmonicsChangeSignal m_harmonicAdded;
	HarmonicsChangeSignal m_harmonicDeleted;
	HarmonicsChangeSignal m_currentIndexChanged;
};
