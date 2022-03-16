#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "mathplot.h"
#include "HarmonicsList.h"

class CChartsView : public mpWindow
{
public:
    CChartsView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
private:
    std::shared_ptr<CHarmonicsList> m_model;

    mpFXYVector* m_chart;
    wxPen m_pen;

    sig::scoped_connection m_addHarmonicConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
    sig::scoped_connection m_changeCurrentHarmonic;
    sig::scoped_connection m_changeCurrentHarmonicIndex;

    void UpdateChart();
    void DeleteChart();
    void AddChart();
};
