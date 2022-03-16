#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
class CCoordinateTableController;
#include "CoordinateTableController.h"
#include <wx/grid.h>

class CCoordinateTableView : public wxGrid
{
public:
    CCoordinateTableView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
private:
    std::unique_ptr<CCoordinateTableController> m_controller;

    sig::scoped_connection m_addHarmonicConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
    sig::scoped_connection m_changeCurrentHarmonic;
    sig::scoped_connection m_changeCurrentHarmonicIndex;

    void UpdateTable();
    void ResetTable();
};
