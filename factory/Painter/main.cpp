#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/CShapeFactory.h"
#include "CPainter.h"
#include "../libpainter/CCanvas.h"
#include <fstream>

using namespace std;

void Help()
{
	std::cout << "rectangle <left top point> <right bottom point> <color>" << std::endl;
	std::cout << "triangle <point1> <point2> <point3> <color>" << std::endl;
	std::cout << "ellipse <center point> <horizontal radius> <vertical radius> <color>" << std::endl;
	std::cout << "regular_polygon <center point> <radius> <vertex count> <color>" << std::endl;
}

int main()
{
	Help();
	CShapeFactory factory;
	CDesigner designer(factory);
	std::ifstream shapes("shapes.txt");
	CPictureDraft draft = designer.CreateDraft(shapes);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 30;

	sf::RenderWindow window(sf::VideoMode(600, 600), "Shapes");
	CCanvas canvas(window);
	CPainter painter;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(255, 255, 255));

		painter.DrawPicture(draft, canvas);

		window.display();
	}

	return 0;
}

