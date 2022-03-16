#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
class CChartsView;
#include "ChartsView.h"

class CChartsController
{
public:
	CChartsController(std::shared_ptr<CHarmonicsList> model, CChartsView& view);
	std::shared_ptr<CHarmonic> GetCurrentHarmonic() const;
	GraphPoints GetGraphPoints() const;
	size_t GetHarmonicsCount() const;
private:
	std::shared_ptr<CHarmonicsList> m_model;
	CChartsView& m_view;
};