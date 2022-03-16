#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
class CUpdateHarmonicView;
#include "UpdateHarmonicView.h"

class CUpdateHarmonicController
{
public:
	CUpdateHarmonicController(std::shared_ptr<CHarmonicsList> model, CUpdateHarmonicView& view);
	std::shared_ptr<CHarmonic> GetCurrentHarmonic();
	size_t GetHarmonicsCount() const;
private:
	std::shared_ptr<CHarmonicsList> m_model;
	CUpdateHarmonicView& m_view;
};