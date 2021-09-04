#pragma once
#include <iostream>
#include <assert.h>

#include "test/test.h"
#include "LRT.h"

#include "Canvas.h"

void CanvasTest()
{
	std::cout << "Canvas Test.....";

	{
		/* Create a canvas */
		LRT::Canvas cav(10, 20);

		LRT::Canvas copy_cav = cav;
		copy_cav.SetPixel(0, 1, LRT::Colors::mangenta);

		assert(cav.GetWidth() == 10 && cav.GetHeight() == 20);
		assert(cav.GetPixel(0, 1) == LRT::Colors::black);

		assert(copy_cav.GetWidth() == 10 && copy_cav.GetHeight() == 20);
		assert(copy_cav.GetPixel(0, 1) == LRT::Colors::mangenta);
	}



	std::cout << "OK\n";
}