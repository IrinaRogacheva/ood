#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "HarmonicsList.h"
#include <wx/grid.h>

class CCoordinateTableView : public wxGrid
{
public:
    CCoordinateTableView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
private:
    std::shared_ptr<CHarmonicsList> m_model;

    sig::scoped_connection m_addHarmonicConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
    std::vector<sig::scoped_connection> m_changeAddedHarmonicVector;

    void UpdateTable();
    void ResetTable();
};
