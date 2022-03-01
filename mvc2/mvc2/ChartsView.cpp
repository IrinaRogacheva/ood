#include "ChartsView.h"

CChartsView::CChartsView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
	: mpWindow(parent, wxID_ANY, wxPoint(20, 180), wxSize(440, 170), wxSIMPLE_BORDER)
{
    m_controller = std::make_unique<CChartsController>(model, *this);

    AddLayer(new mpScaleX("x"));
    AddLayer(new mpScaleY("y"));

    m_addHarmonicConnection = model->DoOnHarmonicAdded([=] {
        CreateChart();
    });
    CreateChart();
    m_changeCurrentHarmonic = model->GetHarmonicAtIndex(0)->DoOnHarmonicChanged([=] {
        CalculateGraphPoints(m_charts[0], m_controller->GetCurrentHarmonic());
        Fit();
    });
    m_changeCurrentHarmonicIndex = model->DoOnCurrentIndexChanged([=] {
        ChangeCurrentChart(m_controller->GetCurrentIndex());
        m_changeCurrentHarmonic = m_controller->GetCurrentHarmonic()->DoOnHarmonicChanged([=] {
            CalculateGraphPoints(m_charts[m_controller->GetCurrentIndex()], m_controller->GetCurrentHarmonic());
            Fit();
        });
    });
    ChangeCurrentChart(0);
    m_deleteHarmonicConnection = model->DoOnHarmonicDeleted([=] {
        DeleteChart();
    });
}

void CChartsView::ChangeCurrentChart(size_t index)
{
    if (CountAllLayers() > 2)
    {
        DelLayer(GetLayer(2));
    }
    wxPen pen = wxPen(*wxRED);
    m_charts[index]->SetPen(pen);
    AddLayer(m_charts[index]);
    Fit();
}

void CChartsView::DeleteChart()
{
    DelLayer(GetLayer(2));
}

void CChartsView::CreateChart()
{
    m_charts.push_back(CreateChart(m_controller->GetCurrentHarmonic()));
}

mpFXYVector* CChartsView::CreateChart(std::shared_ptr<CHarmonic> harmonic)
{
    mpFXYVector* chart = new mpFXYVector();
    CalculateGraphPoints(chart, harmonic);
    return chart;
}

void CChartsView::CalculateGraphPoints(mpFXYVector* chart, std::shared_ptr<CHarmonic> harmonic)
{
    std::vector<double> x;
    std::vector<double> y;
    double n = -10;
    for (size_t i = 0; i < 200; i++)
    {
        x.push_back(n);
        if (harmonic->GetFunctionType() == HarmonicFunctionType::SIN)
        {
            y.push_back(harmonic->GetAmplitude() * sin(harmonic->GetFrequency() * n + harmonic->GetPhase()));
        }
        else
        {
            y.push_back(harmonic->GetAmplitude() * cos(harmonic->GetFrequency() * n + harmonic->GetPhase()));
        }
        n += 0.1;
    }

    chart->SetData(x, y);

    chart->SetContinuity(true);
}
