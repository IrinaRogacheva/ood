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
private:
	std::shared_ptr<CHarmonicsList> m_model;
	CHarmonicsListView& m_view;
};