#pragma once
#include <iostream>
#include <assert.h>

#include "test/test.h"
#include "LRT.h"

void ProjectileTest()
{
	const LRT::vec3 gravity(  0.0f, -0.2f, 0.0f);
	const LRT::vec3    wind( -0.01f,  0.0f, 0.0f);

	LRT::vec3 proj_pos(1.0f, 1.0f, 0.0f);

	LRT::vec3 proj_vel(1.0f, 1.8f, 0.0f);
	proj_vel.normalize();

	const float initial_speed = 11.25f;

	proj_vel *= initial_speed; // speed

	std::cout << "Projectile Test \n";
	std::cout << "Started configuration: \n";
	std::cout << "Gravity: [" << gravity.x << ", " << gravity.y << ", " << gravity.z << "]\n";
	std::cout << "Wind   : [" <<    wind.x << ", " <<    wind.y << ", " <<    wind.z << "]\n";

	std::cout << "Proj Pos:  [" << proj_pos.x << ", " << proj_pos.y << ", " << proj_pos.z << "]\n";
	std::cout << "Proj Vel:  [" << proj_vel.x << ", " << proj_vel.y << ", " << proj_vel.z << "]\n";
	std::cout << "Proj Speed: " << initial_speed << "\n";

	const int MaxNumberOfTicks = 500;
	int numberOfTicks = 0;

	LRT::Canvas cav(900, 550);

	while (proj_pos.y >= 0.0f && numberOfTicks <= MaxNumberOfTicks)
	{
		proj_pos = proj_pos + proj_vel;
		proj_vel = proj_vel + gravity + wind;


		uint32_t c_x = (uint32_t)proj_pos.x;
		uint32_t c_y = cav.GetHeight() - (uint32_t)(proj_pos.y);

		if(c_x >= 0 && c_x < cav.GetWidth() && c_y >= 0 && c_y < cav.GetHeight())
			cav.SetPixel(c_x, c_y, LRT::Colors::green);

		numberOfTicks++;
	}


	std::cout << "Report: \n";

	std::cout << "Ticks:     " << numberOfTicks << "\n";
	std::cout << "Proj Pos: [" << proj_pos.x << ", " << proj_pos.y << ", " << proj_pos.z << "]\n";
	std::cout << "Proj Vel: [" << proj_vel.x << ", " << proj_vel.y << ", " << proj_vel.z << "]\n";

	cav.SaveToFile("Output/ProjectileTest.PPM");
	std::cout << "File Output/ProjectileTest.PPM Saved!!!\n";

}