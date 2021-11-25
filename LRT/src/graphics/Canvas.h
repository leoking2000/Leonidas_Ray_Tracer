#pragma once
#include "LRTMath.h"

namespace LRT
{
	class Canvas
	{
	public:
		Canvas(u32 width, u32 height, Color c = LRT::Colors::black);

		Canvas(const Canvas& other);
		Canvas& operator=(const Canvas& other);

		bool operator==(const Canvas& other);
		bool operator!=(const Canvas& other);

		Canvas(Canvas&& other);
		Canvas& operator=(Canvas&& other);

		~Canvas();

	public:
		inline u32 GetWidth()  const { return m_width; }
		inline u32 GetHeight() const { return m_height; }

		void Clear(const Color& c);

		Color GetPixel(u32 x, u32 y) const;
		void  SetPixel(u32 x, u32 y, const Color& c);

		void SaveToFile(const char* filename); // saves the canvas into a ppm file.

	private:
		u32 m_width;
		u32 m_height;
		Color* m_data; // color array | GetPixel(x, y) => m_data[ y * m_width + x ]
	};
}