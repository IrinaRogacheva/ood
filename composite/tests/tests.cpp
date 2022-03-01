#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../composite/CGroup.h"
#include "../composite/CRectangle.h"
#include "../composite/CTriangle.h"
#include "../composite/CEllipse.h"

SCENARIO("empty group")
{
	GIVEN("created empty group")
	{
		CGroup group;

		WHEN("get count of shapes")
		{
			THEN("group has zero shapes")
			{
				REQUIRE(group.GetShapesCount() == 0);
			}
		}

		AND_WHEN("get frame of group")
		{
			THEN("frame of group is nullopt")
			{
				REQUIRE(group.GetFrame() == std::nullopt);
			}
		}

		AND_WHEN("set frame")
		{
			THEN("got exception that group is empty")
			{
				REQUIRE_THROWS_WITH(group.SetFrame({ 20, 20, 100, 100 }), "Shape group is empty");
			}
		}

		AND_WHEN("get group")
		{
			THEN("it's not nullptr")
			{
				REQUIRE(group.GetGroup() != nullptr);
			}
		}

		AND_WHEN("add empty group")
		{
			group.InsertShape(std::make_shared<CGroup>());
			THEN("frame of the group is nullopt")
			{
				REQUIRE(group.GetFrame() == std::nullopt);
			}
		}

		AND_WHEN("get color from outlineStyle")
		{
			THEN("color is nullopt")
			{
				REQUIRE(group.GetOutlineStyle()->GetColor() == std::nullopt);
			}
		}

		AND_WHEN("get color from fillStyle")
		{
			THEN("color is nullopt")
			{
				REQUIRE(group.GetFillStyle()->GetColor() == std::nullopt);
			}
		}

		AND_WHEN("insert shape in the end")
		{
			group.InsertShape(std::make_shared<CRectangle>(PointD{ 20, 20 }, 100, 100));
			THEN("shape was inserted")
			{
				REQUIRE(group.GetShapesCount() == 1);
			}
		}

		AND_WHEN("insert shape at index 1")
		{
			THEN("got the exception")
			{
				REQUIRE_THROWS_AS(group.InsertShape(std::make_shared<CRectangle>(PointD{ 20, 20 }, 100, 100), 1), std::out_of_range);
			}
		}

		AND_WHEN("get shape at index 0")
		{
			THEN("got the exception")
			{
				REQUIRE_THROWS_AS(group.GetShapeAtIndex(0), std::out_of_range);
			}
		}

		AND_WHEN("delete shape at index 0")
		{
			THEN("got the exception")
			{
				REQUIRE_THROWS_AS(group.RemoveShapeAtIndex(0), std::out_of_range);
			}
		}
	}
}

SCENARIO("not empty group")
{
	GIVEN("group with shapes")
	{
		CGroup group;
		group.InsertShape(std::make_shared<CTriangle>(PointD{ 200, 400 }, PointD{ 300, 200 }, PointD{ 400, 400 }));
		group.InsertShape(std::make_shared<CRectangle>(PointD{ 450, 350 }, 70, 50));
		group.InsertShape(std::make_shared<CEllipse>(PointD{ 192, 212 }, 50, 50));

		WHEN("get count of shapes")
		{
			THEN("group has 3 shapes")
			{
				REQUIRE(group.GetShapesCount() == 3);
			}
		}

		WHEN("delete shape")
		{
			group.RemoveShapeAtIndex(2);
			THEN("shape was deleted")
			{
				REQUIRE(group.GetShapesCount() == 2);
			}
		}

		AND_WHEN("get frame of group")
		{
			RectD frame = *group.GetFrame();

			THEN("frame of group is nullopt")
			{
				REQUIRE(frame.left == 192);
				REQUIRE(frame.top == 200);
				REQUIRE(frame.width == 328);
				REQUIRE(frame.height == 200);
			}
		}

		AND_WHEN("set frame")
		{
			group.SetFrame({ 20, 20, 100, 100 });
			THEN("frame was changed")
			{
				RectD frame = *group.GetFrame();
				REQUIRE(frame.left == 20);
				REQUIRE(frame.top == 20);
				REQUIRE(frame.width == 100);
				REQUIRE(frame.height == 100);
			}
		}

		AND_WHEN("get color from outlineStyle")
		{
			THEN("color is 0x000000")
			{
				REQUIRE(group.GetOutlineStyle()->GetColor() == 0x000000);
			}
		}

		AND_WHEN("get color from fillStyle")
		{
			THEN("color is 0xffffff")
			{
				REQUIRE(group.GetFillStyle()->GetColor() == 0xffffff);
			}
		}

		AND_WHEN("change fill color of one shape")
		{
			group.GetShapeAtIndex(0)->GetFillStyle()->SetColor(0xaabbcc);

			THEN("color of group should be nullopt")
			{
				REQUIRE(group.GetFillStyle()->GetColor() == std::nullopt);
			}
		}

		AND_WHEN("change fill color of all group")
		{
			group.GetFillStyle()->SetColor(0xaabbcc);

			THEN("color of group should be 0xaabbcc")
			{
				REQUIRE(group.GetFillStyle()->GetColor() == 0xaabbcc);
			}
		}

		AND_WHEN("change outline color of one shape")
		{
			group.GetShapeAtIndex(0)->GetOutlineStyle()->SetColor(0xaabbcc);

			THEN("color of group should be nullopt")
			{
				REQUIRE(group.GetOutlineStyle()->GetColor() == std::nullopt);
			}
		}

		AND_WHEN("change outline color of all group")
		{
			group.GetOutlineStyle()->SetColor(0xaabbcc);

			THEN("color of group should be 0xaabbcc")
			{
				REQUIRE(group.GetOutlineStyle()->GetColor() == 0xaabbcc);
			}
		}
	}
}