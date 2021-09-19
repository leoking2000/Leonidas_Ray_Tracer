#include "Canvas.h"
#include <assert.h>
#include <utility>
#include <fstream>
#include <string>

LRT::Canvas::Canvas(uint32_t width, uint32_t height)
    :
    m_width(width),
    m_height(height),
    m_data(new Color[width * height])
{
    Clear(Colors::black);
}

LRT::Canvas::Canvas(const LRT::Canvas& other)
    :
    m_width(other.m_width),
    m_height(other.m_height),
    m_data(new Color[other.m_width * other.m_height])
{
    for (size_t i = 0; i < m_width * m_height; i++)
    {
        m_data[i] = other.m_data[i];
    }
}

LRT::Canvas& LRT::Canvas::operator=(const LRT::Canvas& other)
{
    if (this == &other) return *this;

    m_width = other.GetWidth();
    m_height = other.GetHeight();

    delete[] m_data;
    m_data = new Color[m_width * m_height];

    for (size_t i = 0; i < m_width * m_height; i++)
    {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

bool LRT::Canvas::operator==(const Canvas& other)
{
    for (size_t i = 0; i < m_width * m_height; i++)
    {
        if (m_data[i] == other.m_data[i])
        {
            return false;
        }
    }

    return true;
}

LRT::Canvas::Canvas(LRT::Canvas&& other)
    :
    m_width(other.m_width),
    m_height(other.m_height),
    m_data(other.m_data)
{
    other.m_width = 0;
    other.m_height = 0;
    other.m_data = nullptr;
}

LRT::Canvas& LRT::Canvas::operator=(LRT::Canvas&& other)
{
    if (this == &other) return *this;

    m_width  = other.m_width;
    m_height = other.m_height;

    delete[] m_data;
    m_data = other.m_data;

    other.m_width = 0;
    other.m_height = 0;
    other.m_data = nullptr;

    return *this;
}

LRT::Canvas::~Canvas()
{
    delete[] m_data;
}

void LRT::Canvas::Clear(const Color& c)
{
    for (size_t i = 0; i < m_width * m_height; i++)
    {
        m_data[i] = c;
    }
}

LRT::Color LRT::Canvas::GetPixel(uint32_t x, uint32_t y) const
{
    assert(x >= 0);
    assert(x < m_width);
    assert(y >= 0);
    assert(y < m_height);

    return m_data[y * m_width + x];
}

void LRT::Canvas::SetPixel(uint32_t x, uint32_t y, const Color& c)
{
    assert(x >= 0);
    assert(x < m_width);
    assert(y >= 0);
    assert(y < m_height);

    m_data[y * m_width + x] = c;
}

void LRT::Canvas::SaveToFile(const char* filename)
{
    // the PPM file format must have 70 characters per line or less.
    // a pixel will take at maximum 12 characters.  example: "255 255 255 "
    // so if we write 5 pixels per line we have 12*5 = 60( < 70) characters per line at maximum.
    constexpr uint32_t MaxPixelsPerLine = 5;

    std::ofstream ppm_file;
    ppm_file.open(filename, std::ios::out | std::ios::trunc);

    ppm_file << "P3\n";
    ppm_file << std::to_string(m_width) << " " << std::to_string(m_height) << "\n";
    ppm_file << "255" << "\n";

    uint32_t counter = 0; // counts the pixels writen in on line

    for (size_t i = 0; i < m_width * m_height; i++)
    {
        Color* pixel = &m_data[i];

        uint32_t r = LRT::clamp<uint32_t>(uint32_t(pixel->r * 255.0f), 0, 255);
        uint32_t g = LRT::clamp<uint32_t>(uint32_t(pixel->g * 255.0f), 0, 255);
        uint32_t b = LRT::clamp<uint32_t>(uint32_t(pixel->b * 255.0f), 0, 255);

        ppm_file << std::to_string(r) << " " << std::to_string(g) << " " << std::to_string(b) << " ";

        counter++;
        if (counter == MaxPixelsPerLine)
        {
            ppm_file << "\n";
            counter = 0;
        }
    }

    ppm_file << "\n";

    ppm_file.close();
}
