#include "ChartsView.h"

CChartsView::CChartsView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
    : mpWindow(parent, wxID_ANY, wxPoint(20, 180), wxSize(440, 170), wxSIMPLE_BORDER)
{
    m_controller = std::make_unique<CChartsController>(model, *this);

    AddLayer(new mpScaleX("x"));
    AddLayer(new mpScaleY("y"));

    m_chart = new mpFXYVector();
    m_pen = wxPen(*wxRED);
    m_chart->SetPen(m_pen);
    AddLayer(m_chart);

    m_addHarmonicConnection = model->DoOnHarmonicAdded([=] {
        AddChart();
        UpdateChart();
    });
    UpdateChart();
    m_changeCurrentHarmonic = m_controller->GetCurrentHarmonic()->DoOnHarmonicChanged([=] {
        UpdateChart();
    });

    m_changeCurrentHarmonicIndex = model->DoOnCurrentIndexChanged([=] {
        m_changeCurrentHarmonic = m_controller->GetCurrentHarmonic()->DoOnHarmonicChanged([=] {
            UpdateChart();
        });
    });

    m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
        DeleteChart();
        UpdateChart();
    });
}

void CChartsView::UpdateChart()
{
    GraphPoints points = m_controller->GetGraphPoints();

    m_chart->SetData(points.x, points.y);
    m_chart->SetContinuity(true);

    mpWindow::Fit();
}

void CChartsView::DeleteChart()
{
    if (m_controller->GetHarmonicsCount() == 0)
    {
        m_pen = wxPen(*wxBLACK);
        m_chart->SetPen(m_pen);
    }
}

void CChartsView::AddChart()
{
    if (m_controller->GetHarmonicsCount() == 1)
    {
        m_pen = wxPen(*wxRED);
        m_chart->SetPen(m_pen);
    }
}
