#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "mathplot.h"
#include "HarmonicsList.h"
class CChartsController;
#include "ChartsController.h"

class CChartsView : public mpWindow
{
public:
    CChartsView(wxWindow* parent, std::shared_ptr<CHarmonicsList> model);
private:
    std::vector<mpFXYVector*> m_charts;

    std::unique_ptr<CChartsController> m_controller;

    sig::scoped_connection m_addHarmonicConnection;
    sig::scoped_connection m_deleteHarmonicConnection;
    sig::scoped_connection m_changeCurrentHarmonic;
    sig::scoped_connection m_changeCurrentHarmonicIndex;

    void ChangeCurrentChart(size_t index);
    void DeleteChart();
    void CreateChart();

    mpFXYVector* CreateChart(std::shared_ptr<CHarmonic> harmonic);
    void CalculateGraphPoints(mpFXYVector* chart, std::shared_ptr<CHarmonic> harmonic);
};
