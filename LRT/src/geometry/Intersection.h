#pragma once
#include "LRTMath.h"

namespace LRT
{
	class Intersection
	{
	public:
		f32 t;
		u32 shapeID; // this is an Index to find the shape of the intersection
	public:
		Intersection(f32 t, u32 index);

		bool operator==(const Intersection& other) const;
		bool operator!=(const Intersection& other) const;
	};
}


