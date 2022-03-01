#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
class CAddHarmonicView;
#include "AddHarmonicView.h"

class CAddHarmonicController
{
public:
	CAddHarmonicController(std::shared_ptr<CHarmonicsList> model, CAddHarmonicView& view);
	void AddHarmonic(std::shared_ptr<CHarmonic> harmonic);
private:
	std::shared_ptr<CHarmonicsList> m_model;
	CAddHarmonicView& m_view;
};
