#include "stdafx.h"
#include "Designer.h"
#include <iostream>

using namespace std;

CDesigner::CDesigner(IShapeFactory & factory)
	:m_factory(factory)
{
}

CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream & inputData)
{
	CPictureDraft draft;
	string line;
	while (getline(inputData, line))
	{
		try
		{
			auto shape = m_factory.CreateShape(line);
			draft.AddShape(std::move(shape));
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return draft;
}
