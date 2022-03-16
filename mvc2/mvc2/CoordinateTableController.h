#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
class CCoordinateTableView;
#include "CoordinateTableView.h"

class CCoordinateTableController
{
public:
	CCoordinateTableController(std::shared_ptr<CHarmonicsList> model, CCoordinateTableView& view);
	std::shared_ptr<CHarmonic> GetCurrentHarmonic() const;
	GraphPoints GetGraphPoints() const;
	size_t GetHarmonicsCount() const;
private:
	std::shared_ptr<CHarmonicsList> m_model;
	CCoordinateTableView& m_view;
};