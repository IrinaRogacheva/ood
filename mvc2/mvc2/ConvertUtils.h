#pragma once
#include "wx/wx.h"
#include <iomanip>
#include <sstream>

double ConvertWxStringToDouble(const wxString& str);
std::string ConvertDoubleToString(double num);