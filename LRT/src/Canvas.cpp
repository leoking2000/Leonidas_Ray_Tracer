#include "Canvas.h"
#include <assert.h>
#include <utility>

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
