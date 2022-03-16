#include "CoordinateTableView.h"
#include "ConvertUtils.h"

CCoordinateTableView::CCoordinateTableView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
    : wxGrid(parent, wxID_ANY)
{
	m_controller = std::make_unique<CCoordinateTableController>(model, *this);

    CreateGrid(201, 2);
    HideRowLabels();
    SetColLabelValue(0, wxString("x"));
    SetColLabelValue(1, wxString("y"));
    SetDefaultColSize(225);
    SetColLabelAlignment(wxALIGN_LEFT, wxALIGN_CENTRE);
    DisableDragColSize();
    DisableDragRowSize();
    for (size_t i = 0; i <= 200; i++)
    {
        SetReadOnly(i, 0);
        SetReadOnly(i, 1);
    }

    m_addHarmonicConnection = model->DoOnHarmonicAdded([=] {
        UpdateTable();
    });
    UpdateTable();
    m_changeCurrentHarmonic = m_controller->GetCurrentHarmonic()->DoOnHarmonicChanged([=] {
        UpdateTable();
    });

    m_changeCurrentHarmonicIndex = model->DoOnCurrentIndexChanged([=] {
        m_changeCurrentHarmonic = m_controller->GetCurrentHarmonic()->DoOnHarmonicChanged([=] {
            UpdateTable();
        });
    });

    m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
        if (m_controller->GetHarmonicsCount() == 0)
        {
            ResetTable();
        }
        else
        {
            UpdateTable();
        }
    });
}

void CCoordinateTableView::ResetTable()
{
    for (size_t i = 0; i <= 200; i++)
    {
        SetCellValue(i, 0, "");
        SetCellValue(i, 1, "");
    }
}

void CCoordinateTableView::UpdateTable()
{
    GraphPoints points = m_controller->GetGraphPoints();

    for (size_t i = 0; i <= 200; i++)
    {
        SetCellValue(i, 0, ConvertDoubleToString(points.x[i]));
        SetCellValue(i, 1, ConvertDoubleToString(points.y[i]));
    }
}