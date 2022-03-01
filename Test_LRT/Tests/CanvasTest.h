#pragma once
#include "gtest/gtest.h"

#include "LRT.h"

TEST(CanvasTest, Create_canvas)
{
	/* Create a canvas */
	LRT::Canvas cav(10, 20);

	LRT::Canvas copy_cav = cav;

	copy_cav.Clear(Colors::white);
	copy_cav.SetPixel(0, 1, Colors::mangenta);
	copy_cav.SetPixel(1, 0, Colors::cyan);

	EXPECT_TRUE(cav.GetWidth() == 10 && cav.GetHeight() == 20);
	EXPECT_TRUE(cav.GetPixel(0, 1) == Colors::black);

	EXPECT_TRUE(copy_cav.GetWidth() == 10 && copy_cav.GetHeight() == 20);
	EXPECT_TRUE(copy_cav.GetPixel(0, 1) == Colors::mangenta);

	copy_cav.SetPixel(0, 0, Colors::red);
	copy_cav.SetPixel(copy_cav.GetWidth() - 1, 0, Colors::green);
	copy_cav.SetPixel(copy_cav.GetWidth() - 1, copy_cav.GetHeight() - 1, Colors::blue);
	copy_cav.SetPixel(0, copy_cav.GetHeight() - 1, Colors::yellow);

	copy_cav.SaveToFilePPM("Output/Test/CanvasTest.PPM");
}

TEST(CanvasTest, test2)
{
	LRT::Canvas cav(255, 255);

	for (u32 y = 0; y < cav.GetHeight(); y++)
	{
		for (u32 x = 0; x < cav.GetWidth(); x++)
		{
			cav.SetPixel(x, y, Color(x / 255.0f, y / 255.0f, 0.0f));
		}
	}

	cav.SaveToFilePPM("Output/Test/Test.PPM");
}
