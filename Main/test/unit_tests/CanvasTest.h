#pragma once
#include <iostream>
#include <assert.h>

#include "test/test.h"
#include "LRT.h"

void CanvasTest()
{
	std::cout << "Canvas Test.....";

	{
		/* Create a canvas */
		LRT::Canvas cav(10, 20);

		LRT::Canvas copy_cav = cav;

		copy_cav.Clear(LRT::Colors::white);
		copy_cav.SetPixel(0, 1, LRT::Colors::mangenta);
		copy_cav.SetPixel(1, 0, LRT::Colors::cyan);

		assert(cav.GetWidth() == 10 && cav.GetHeight() == 20);
		assert(cav.GetPixel(0, 1) == LRT::Colors::black);

		assert(copy_cav.GetWidth() == 10 && copy_cav.GetHeight() == 20);
		assert(copy_cav.GetPixel(0, 1) == LRT::Colors::mangenta);

		copy_cav.SetPixel(0, 0, LRT::Colors::red);
		copy_cav.SetPixel(copy_cav.GetWidth() - 1, 0, LRT::Colors::green);
		copy_cav.SetPixel(copy_cav.GetWidth() - 1, copy_cav.GetHeight() - 1, LRT::Colors::blue);
		copy_cav.SetPixel(0, copy_cav.GetHeight() - 1, LRT::Colors::yellow);

		copy_cav.SaveToFile("Output/CanvasTest.PPM");
	}



	std::cout << "OK\n";
}