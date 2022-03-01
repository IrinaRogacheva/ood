#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
class CHarmonicsListView;
#include "HarmonicsListView.h"

class CHarmonicsListController
{
public:
	CHarmonicsListController(std::shared_ptr<CHarmonicsList> model, CHarmonicsListView& view);
	void DeleteHarmonic(size_t index);
	void SetCurrentIndex(size_t index);
	size_t GetCurrentIndex() const;
	std::shared_ptr<CHarmonic> GetCurrentHarmonic() const;
	std::shared_ptr<CHarmonic> GetLastHarmonic() const;
private:
	std::shared_ptr<CHarmonicsList> m_model;
	CHarmonicsListView& m_view;
};