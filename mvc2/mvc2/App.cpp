#include "App.h"

wxIMPLEMENT_APP(CApp);

bool CApp::OnInit()
{
    m_frame = new wxFrame(NULL, wxID_ANY, "Chart Drawer", wxPoint(400, 200), wxSize(500, 410));
    m_frame->SetBackgroundColour(*wxWHITE);
    wxPanel* panel = new wxPanel(m_frame, wxID_ANY, wxPoint(0, 0), wxSize(500, 1), wxBORDER_SIMPLE);

    std::shared_ptr<CHarmonicsList> model = std::make_shared<CHarmonicsList>();
    m_harmonicsListView = new CHarmonicsListView(m_frame, model);
    m_updateHarmonicView = new CUpdateHarmonicView(m_frame, model);
    m_chartsView = new CChartsView(m_frame, model);

    m_frame->Show(true);

    return true;
}
