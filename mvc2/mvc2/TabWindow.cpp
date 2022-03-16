#include "TabWindow.h"

CTabWindow::CTabWindow(wxWindow* parent, std::shared_ptr<CHarmonicsList> model)
	: wxNotebook(parent, wxID_ANY, wxPoint(20, 180), wxSize(440, 170)/*, wxSIMPLE_BORDER*/)
{
	CChartsView* chartsView = new CChartsView(this, model);
	CCoordinateTableView* tableView = new CCoordinateTableView(this, model);
	InsertPage(0, chartsView, wxString("Chart"), true);
	InsertPage(1, tableView, wxString("Table"));
}
