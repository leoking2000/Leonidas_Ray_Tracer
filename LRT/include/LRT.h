#pragma once
#include "Canvas.h"
#include "geometry.h"

namespace LRT
{
	LRT::Color LRTAPI lighting(const Material& mat, 
							   const PointLight& light, 
							   const LRT::vec3& point, 
							   const LRT::vec3& view, 
							   const LRT::vec3& normal);
}