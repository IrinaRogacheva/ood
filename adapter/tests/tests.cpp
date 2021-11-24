#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../lwtask/app.h"

TEST_CASE("drawing by adapter")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);
	app::CModernGraphicsLibAdapter adapter(renderer);

	adapter.MoveTo(3, 5);
	adapter.LineTo(12, 23);

	REQUIRE(oss.str() == "<draw>\n  <line fromX=\"3\" fromY=\"5\" toX=\"12\" toY=\"23\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n  </line>\n");
	adapter; //destruction
	REQUIRE(oss.str() == "<draw>\n  <line fromX=\"3\" fromY=\"5\" toX=\"12\" toY=\"23\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n  </line>\n</draw>\n");
}

TEST_CASE("when drawing by adapter without setting the start point drawing is starting from point { 0, 0 }")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);
	app::CModernGraphicsLibAdapter adapter(renderer);

	adapter.LineTo(12, 23);

	REQUIRE(oss.str() == "<draw>\n  <line fromX=\"0\" fromY=\"0\" toX=\"12\" toY=\"23\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n  </line>\n");

	REQUIRE(oss.str() == "<draw>\n  <line fromX=\"0\" fromY=\"0\" toX=\"12\" toY=\"23\">\n    <color r=\"0\" g=\"0\" b=\"0\" a=\"0\" />\n  </line>\n</draw>\n");
}

TEST_CASE("setting the color")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);
	app::CModernGraphicsLibAdapter adapter(renderer);

	adapter.SetColor(0xffffff);

	renderer.BeginDraw();

	adapter.LineTo(12, 23);

	REQUIRE(oss.str() == "<draw>\n  <line fromX=\"0\" fromY=\"0\" toX=\"12\" toY=\"23\">\n    <color r=\"255\" g=\"255\" b=\"255\" a=\"1\" />\n  </line>\n");

	renderer.EndDraw();
	REQUIRE(oss.str() == "<draw>\n  <line fromX=\"0\" fromY=\"0\" toX=\"12\" toY=\"23\">\n    <color r=\"255\" g=\"255\" b=\"255\" a=\"1\" />\n  </line>\n</draw>\n");
}