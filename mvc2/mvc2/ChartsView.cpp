#include "ChartsView.h"
#include "GraphPoints.h"

CChartsView::CChartsView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
    : mpWindow(parent, wxID_ANY, wxPoint(20, 180), wxSize(440, 170), wxSIMPLE_BORDER)
    , m_model(model)
{
    AddLayer(new mpScaleX("x"));
    AddLayer(new mpScaleY("y"));

    m_chart = new mpFXYVector();
    m_pen = wxPen(*wxRED);
    m_chart->SetPen(m_pen);
    AddLayer(m_chart);

    m_addHarmonicConnection = model->DoOnHarmonicAdded([=] {
        AddChart();
        UpdateChart();

        m_changeAddedHarmonicVector.push_back(sig::scoped_connection());
        m_changeAddedHarmonicVector[m_changeAddedHarmonicVector.size() - 1] = m_model->GetHarmonicAtIndex(m_model->GetHarmonicsCount() - 1)->DoOnHarmonicChanged([=] {
            UpdateChart();
        });
    });
    
    UpdateChart();
    m_changeAddedHarmonicVector.push_back(sig::scoped_connection());
    m_changeAddedHarmonicVector[m_changeAddedHarmonicVector.size() - 1] = m_model->GetHarmonicAtIndex(m_model->GetHarmonicsCount() - 1)->DoOnHarmonicChanged([=] {
        UpdateChart();
    });

    m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
        DeleteChart();
        UpdateChart();
    });
}

void CChartsView::UpdateChart()
{
    GraphPoints points;
    double x = -10;
    for (size_t i = 0; i <= 200; i++)
    {
        points.x.push_back(x);
        points.y.push_back(m_model->CalculateFunctionValue(x));
        x += 0.1;
    }
    m_chart->SetData(points.x, points.y);
    m_chart->SetContinuity(true);

    Fit();
}

void CChartsView::DeleteChart()
{
    if (m_model->GetHarmonicsCount() == 0)
    {
        m_pen = wxPen(*wxBLACK);
        m_chart->SetPen(m_pen);
    }
}

void CChartsView::AddChart()
{
    if (m_model->GetHarmonicsCount() == 1)
    {
        m_pen = wxPen(*wxRED);
        m_chart->SetPen(m_pen);
    }
}
