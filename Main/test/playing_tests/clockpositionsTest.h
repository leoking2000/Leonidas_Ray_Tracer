#pragma once
#include <iostream>
#include <assert.h>

#include "LRT.h"

void clockpositionsTest()
{
	LRT::Canvas can(100, 100);

	float wid = can.GetWidth() / 2.0f;
	float hei = can.GetHeight() / 2.0f;

	LRT::mat4 toCanvasSpace = {
		1.0f,  0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		 wid,   hei, 0.0f, 1.0f
	};

	LRT::mat4 rot = LRT::mat4::rotationZ(LRT::PI / 6.0f);

	LRT::vec4 p = LRT::vec4::point(0.0f, 40.0f, 0.0f);

	for (uint32_t i = 0; i < 12; i++)
	{
		LRT::vec4 p_can = p * toCanvasSpace;
		can.SetPixel((uint32_t)p_can.x, (uint32_t)p_can.y, LRT::Colors::white);

		p *= rot;
	}

	can.SaveToFile("Output/clockTest.PPM");
	std::cout << "Clock positions Test Runned\n";
}