#pragma once
#include "LRTMath.h"

namespace LRT
{
	class LRTAPI Canvas
	{
	public:
		Canvas(uint32_t width, uint32_t height);

		Canvas(const Canvas& other);
		Canvas& operator=(const Canvas& other);

		bool operator==(const Canvas& other);

		Canvas(Canvas&& other);
		Canvas& operator=(Canvas&& other);

		~Canvas();

	public:
		inline uint32_t GetWidth()  const { return m_width; }
		inline uint32_t GetHeight() const { return m_height; }

		void Clear(const Color& c);

		Color GetPixel(uint32_t x, uint32_t y) const;
		void  SetPixel(uint32_t x, uint32_t y, const Color& c);

		void SaveToFile(const char* filename); // saves the canvas into a ppm file.

	private:
		uint32_t m_width;
		uint32_t m_height;
		Color* m_data; // color array | GetPixel(x, y) => m_data[ y * m_width + x ]
	};
}