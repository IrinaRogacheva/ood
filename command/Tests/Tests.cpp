#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../DocumentEditor/CDocument.h"
#include "../DocumentEditor/CMenu.h"

SCENARIO("document")
{
	GIVEN("created document")
	{
		CDocument document;

		WHEN("get count of shapes")
		{
			THEN("document has zero items")
			{
				REQUIRE(document.GetItemsCount() == 0);
			}
		}

		AND_WHEN("get title")
		{
			THEN("title is empty string")
			{
				REQUIRE(document.GetTitle() == "");
			}
		}

		AND_WHEN("check if it's possible to redo command")
		{
			THEN("it's not possible to redo")
			{
				REQUIRE(document.CanRedo() == false);
			}
		}

		AND_WHEN("check if it's possible to undo command")
		{
			THEN("it's not possible to undo")
			{
				REQUIRE(document.CanUndo() == false);
			}
		}

		AND_WHEN("set title")
		{
			document.SetTitle("New title");
			THEN("title was changed")
			{
				REQUIRE(document.GetTitle() == "New title");
			}

			WHEN("undo set of title")
			{
				document.Undo();
				THEN("title is empty string again")
				{
					REQUIRE(document.GetTitle() == "");
				}

				WHEN("redo set of title")
				{
					document.Redo();
					THEN("title is 'New title' again")
					{
						REQUIRE(document.GetTitle() == "New title");
					}
				}
			}
		}

		AND_WHEN("insert item at position 1")
		{
			THEN("got the exception")
			{
				REQUIRE_THROWS_WITH(document.InsertParagraph("Paragraph", 1), "Wrong position argument");
			}
		}

		AND_WHEN("get item at position 1")
		{
			THEN("got the exception")
			{
				REQUIRE_THROWS_WITH(document.GetItem(1), "Wrong position argument");
			}
		}

		AND_WHEN("insert item at position 0")
		{
			document.InsertParagraph("Paragraph", 0);
			THEN("item was inserted")
			{
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "Paragraph");
			}

			WHEN("insert one more item at position 0")
			{
				document.InsertParagraph("Another paragraph", 0);
				THEN("item was inserted")
				{
					REQUIRE(document.GetItemsCount() == 2);
				}

				AND_THEN("items on right positions")
				{
					REQUIRE(document.GetItem(1).GetParagraph()->GetText() == "Paragraph");
					REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "Another paragraph");
				}

				AND_WHEN("undo insert of these two items")
				{
					document.Undo();
					document.Undo();
					THEN("no items in document")
					{
						REQUIRE(document.GetItemsCount() == 0);
					}
					WHEN("redo insertion of two items")
					{
						document.Redo();
						document.Redo();
						THEN("these two items are in document again")
						{
							REQUIRE(document.GetItem(1).GetParagraph()->GetText() == "Paragraph");
							REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "Another paragraph");
						}
					}
				}
			}
		}

		AND_THEN("set new text in paragraph")
		{
			document.InsertParagraph("Paragraph", 0);
			document.GetItem(0).GetParagraph()->SetText("New text in paragraph");
			THEN("text in paragraph was changed")
			{
				REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "New text in paragraph");
			}
			WHEN("undo setting of new text in paragraph")
			{
				document.Undo();
				THEN("paragraph has previous text")
				{
					REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "Paragraph");
				}
				WHEN("redo")
				{
					document.Redo();
					THEN("paragraph has new text again")
					{
						REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "New text in paragraph");
					}
				}
			}
		}

		AND_WHEN("delete paragraph element")
		{
			document.InsertParagraph("paragraph", 0);
			document.DeleteItem(0);
			THEN("document has 0 items")
			{
				REQUIRE(document.GetItemsCount() == 0);
			}
			WHEN("undo")
			{
				document.Undo();
				THEN("paragraph is in document")
				{
					REQUIRE(document.GetItem(0).GetParagraph()->GetText() == "paragraph");
				}
				WHEN("redo")
				{
					document.Redo();
					THEN("paragraph is deleted again")
					{
						REQUIRE(document.GetItemsCount() == 0);
					}
				}
			}
		}

		AND_WHEN("insert image")
		{
			document.InsertImage(std::filesystem::path("imagesToInsert/image.jpg"), 800, 600, 0);
			std::string imagePath = document.GetItem(0).GetImage()->GetPath().string();

			THEN("image was inserted")
			{
				REQUIRE(document.GetItemsCount() == 1);
				REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 800);
				REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 600);
			}

			AND_WHEN("undo insert of image")
			{
				document.Undo();
				THEN("there is no image in document")
				{
					REQUIRE(document.GetItemsCount() == 0);
				}
				AND_THEN("image is still in filesystem")
				{
					REQUIRE(std::filesystem::exists(imagePath));
				}
				WHEN("redo insertion of image")
				{
					document.Redo();
					THEN("image is in document again")
					{
						REQUIRE(document.GetItemsCount() == 1);
						REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 800);
						REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 600);
					}
				}
				AND_WHEN("insert paragraph in document")
				{
					document.InsertParagraph("some text", 0);
					THEN("image was deleted from filesystem")
					{
						REQUIRE(!std::filesystem::exists(imagePath));
					}
				}
			}
		}

		AND_WHEN("insert image with wrong path")
		{
			THEN("got exception")
			{
				REQUIRE_THROWS_WITH(document.InsertImage(std::filesystem::path("imagesToInsert/no_image.jpg"), 800, 600, 0), "File does not exist");
			}
		}

		AND_WHEN("insert image with wrong size")
		{
			THEN("got exception")
			{
				REQUIRE_THROWS_WITH(document.InsertImage(std::filesystem::path("imagesToInsert/image.jpg"), 10001, 600, 0), "Wrong size argument. Width and height must be number greater than 1 and less than 10000");
			}
		}

		AND_WHEN("resize an image")
		{
			document.InsertImage(std::filesystem::path("imagesToInsert/image.jpg"), 800, 600, 0);
			document.GetItem(0).GetImage()->Resize(500, 300);
			THEN("size of image was changed")
			{
				REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 500);
				REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
			}
			WHEN("undo resizing of image")
			{
				document.Undo();
				THEN("image has previous size")
				{
					REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 800);
					REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 600);
				}
				WHEN("redo")
				{
					document.Redo();
					THEN("image has new size again")
					{
						REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 500);
						REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 300);
					}
				}
			}
		}

		AND_WHEN("delete image element")
		{
			document.InsertImage(std::filesystem::path("imagesToInsert/image.jpg"), 800, 600, 0);
			document.DeleteItem(0);
			THEN("document has 0 items")
			{
				REQUIRE(document.GetItemsCount() == 0);
			}
			WHEN("undo")
			{
				document.Undo();
				THEN("image is in document")
				{
					REQUIRE(document.GetItem(0).GetImage()->GetWidth() == 800);
					REQUIRE(document.GetItem(0).GetImage()->GetHeight() == 600);
				}
				WHEN("redo")
				{
					document.Redo();
					THEN("image is deleted again")
					{
						REQUIRE(document.GetItemsCount() == 0);
					}
				}
			}
		}

	}
}

SCENARIO("test history")
{
	CDocument document;
	for (size_t i = 0; i < 11; i++)
	{
		document.SetTitle(std::to_string(i));
	}
	WHEN("undo 10 commands")
	{
		for (size_t i = 0; i < 10; i++)
		{
			document.Undo();
		}
		THEN("it's impossible to undo")
		{
			REQUIRE(document.CanUndo() == false);
		}
	}
}

SCENARIO("test menu")
{
	std::stringstream in;
	std::stringstream out;
	CMenu menu(in, out);
	WHEN("execute unknown command")
	{
		in << "command";
		menu.Run();
		THEN("got message about unknown command")
		{
			REQUIRE(out.str() == "Commands list:\n>Unknown command\n>");
		}
	}

	AND_WHEN("add command in menu")
	{
		menu.AddItem("command", "description", [&out]() { out << "command is executing\n"; });
		menu.ShowInstructions();

		THEN("menu has one command")
		{
			REQUIRE(out.str() == "Commands list:\n  command: description\n");
		}
		AND_WHEN("execute added command")
		{
			out.str("");
			out.clear();
			in << "command";
			menu.Run();

			THEN("command is executed")
			{
				REQUIRE(out.str() == "Commands list:\n  command: description\n>command is executing\n>");
			}
		}
	}
}