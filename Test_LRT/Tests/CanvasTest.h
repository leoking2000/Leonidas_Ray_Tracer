#pragma once
#include "gtest/gtest.h"

#include "LRT.h"

TEST(CanvasTest, Create_canvas)
{
	/* Create a canvas */
	LRT::Canvas cav(10, 20);

	LRT::Canvas copy_cav = cav;

	copy_cav.Clear(LRT::Colors::white);
	copy_cav.SetPixel(0, 1, LRT::Colors::mangenta);
	copy_cav.SetPixel(1, 0, LRT::Colors::cyan);

	EXPECT_TRUE(cav.GetWidth() == 10 && cav.GetHeight() == 20);
	EXPECT_TRUE(cav.GetPixel(0, 1) == LRT::Colors::black);

	EXPECT_TRUE(copy_cav.GetWidth() == 10 && copy_cav.GetHeight() == 20);
	EXPECT_TRUE(copy_cav.GetPixel(0, 1) == LRT::Colors::mangenta);

	copy_cav.SetPixel(0, 0, LRT::Colors::red);
	copy_cav.SetPixel(copy_cav.GetWidth() - 1, 0, LRT::Colors::green);
	copy_cav.SetPixel(copy_cav.GetWidth() - 1, copy_cav.GetHeight() - 1, LRT::Colors::blue);
	copy_cav.SetPixel(0, copy_cav.GetHeight() - 1, LRT::Colors::yellow);

	copy_cav.SaveToFile("Output/CanvasTest.PPM");
}
