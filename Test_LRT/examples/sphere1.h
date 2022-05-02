#pragma once
#include "LRT.h"

void Sphere1()
{
	using namespace LRT;

	Scene scean("Input/Scenes/sphere1.json");

	// render
	Canvas c = scean.Render();
	c.SaveToFilePNG("Output/Test/test.png");

}
