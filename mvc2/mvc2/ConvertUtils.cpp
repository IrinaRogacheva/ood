#include "ConvertUtils.h"

double ConvertWxStringToDouble(const wxString& str)
{
	double n;
	str.ToDouble(&n);
	return n;
}

std::string ConvertDoubleToString(double num)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << num;
    std::string s = stream.str();
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s[s.size() - 1] == '.')
    {
        s.erase(s.size() - 1, 1);
    }
    return s;
}