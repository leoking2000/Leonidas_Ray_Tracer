#pragma once
#include "LRTMath.h"
#include <memory>

namespace LRT
{
	class Primitive;

	class Intersection
	{
	public:
		Intersection(f32 distance, u64 pPrimitive);

		bool operator==(const Intersection& other) const;
		bool operator!=(const Intersection& other) const;
	public:
		inline u64 GetPrimitiveID() const
		{
			return m_pPrimitive;
		}

		// from the ray origin to the point of Intersection
		inline f32 GetDistance() const
		{
			return m_distance;
		}
	private:
		f32 m_distance; 
		u64 m_pPrimitive;
	};
}


