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

	copy_cav.SaveToFilePNG("Output/Test/CanvasTest1.png");
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

	cav.SaveToFilePNG("Output/Test/CanvasTest2.png");
}

TEST(CanvasTest, ClockPositionsTest)
{
	LRT::Canvas can(100, 100);

	f32 wid = can.GetWidth() / 2.0f;
	f32 hei = can.GetHeight() / 2.0f;

	glm::mat4 toCanvasSpace = {
		1.0f,  0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		 wid,   hei, 0.0f, 1.0f
	};

	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), LRT::PI / 6.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec4 p = glm::vec4(0.0f, 40.0f, 0.0f, 1.0f);

	for (u32 i = 0; i < 12; i++)
	{
		glm::vec4 p_can = toCanvasSpace * p;
		can.SetPixel((u32)p_can.x, (u32)p_can.y, Colors::white);

		p = rot * p;
	}

	can.SaveToFilePNG("Output/Test/clockTest.png");
}

TEST(CanvasTest, ProjectileTest)
{
	const glm::vec3 gravity(0.0f, -0.2f, 0.0f);
	const glm::vec3    wind(-0.01f, 0.0f, 0.0f);

	glm::vec3 proj_pos(1.0f, 1.0f, 0.0f);

	glm::vec3 proj_vel(1.0f, 1.8f, 0.0f);
	proj_vel = glm::normalize(proj_vel);

	const f32 initial_speed = 11.25f;

	proj_vel *= initial_speed; // speed

	//std::cout << "Projectile Test \n";
	//std::cout << "Started configuration: \n";
	//std::cout << "Gravity: [" << gravity.x << ", " << gravity.y << ", " << gravity.z << "]\n";
	//std::cout << "Wind   : [" << wind.x << ", " << wind.y << ", " << wind.z << "]\n";

	//std::cout << "Proj Pos:  [" << proj_pos.x << ", " << proj_pos.y << ", " << proj_pos.z << "]\n";
	//std::cout << "Proj Vel:  [" << proj_vel.x << ", " << proj_vel.y << ", " << proj_vel.z << "]\n";
	//std::cout << "Proj Speed: " << initial_speed << "\n";

	const u32 MaxNumberOfTicks = 500;
	u32 numberOfTicks = 0;

	LRT::Canvas cav(900, 550);

	while (proj_pos.y >= 0.0f && numberOfTicks <= MaxNumberOfTicks)
	{
		proj_pos = proj_pos + proj_vel;
		proj_vel = proj_vel + gravity + wind;


		u32 c_x = (u32)proj_pos.x;
		u32 c_y = cav.GetHeight() - (u32)(proj_pos.y);

		if (c_x >= 0 && c_x < cav.GetWidth() && c_y >= 0 && c_y < cav.GetHeight())
			cav.SetPixel(c_x, c_y, Colors::green);

		numberOfTicks++;
	}


	//std::cout << "Report: \n";

	//std::cout << "Ticks:     " << numberOfTicks << "\n";
	//std::cout << "Proj Pos: [" << proj_pos.x << ", " << proj_pos.y << ", " << proj_pos.z << "]\n";
	//std::cout << "Proj Vel: [" << proj_vel.x << ", " << proj_vel.y << ", " << proj_vel.z << "]\n";

	cav.SaveToFilePNG("Output/Test/ProjectileTest.png");
}
