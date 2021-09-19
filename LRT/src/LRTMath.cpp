#pragma once
#include "LRTMath.h"

namespace LRT
{
    bool Equal(float a, float b, float epsilon)
    {
        return std::abs(a - b) < epsilon;
    }

    vec3 vec3::zero()
    {
        return vec3(0.0f, 0.0f, 0.0f);
    }

    vec3 vec3::up()
    {
        return vec3(0.0f, 1.0f, 0.0f);
    }

    vec3 vec3::down()
    {
        return vec3(0.0f, -1.0f, 0.0f);
    }

    vec3 vec3::right()
    {
        return vec3(1.0f, 0.0f, 0.0f);
    }

    vec3 vec3::left()
    {
        return vec3(-1.0f, 0.0f, 0.0f);
    }

    vec3 vec3::forward()
    {
        return vec3(0.0f, 0.0f, 1.0f);
    }

    vec3 vec3::back()
    {
        return vec3(0.0f, 0.0f, -1.0f);
    }

    float vec3::distance(const vec3& a, const vec3& b)
    {
        return (a - b).length();
    }

    float vec3::dot(const vec3& a, const vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    vec3 vec3::cross(const vec3& a, const vec3& b)
    {
        return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    vec3 vec3::reflect(const vec3& a, const vec3& normal)
    {
        return a - 2.0f * normal * a.dot(normal);
    }

    float vec3::sqrLength() const
    {
        return this->dot(*this);
    }

    float vec3::length() const
    {
        return std::sqrt(this->dot(*this));
    }

    vec3 vec3::getNormalized() const
    {
        return *this / this->length();
    }

    float vec3::distance(const vec3& a) const
    {
        return (*this - a).length();
    }

    float vec3::dot(const vec3& a) const
    {
        return dot(*this, a);
    }

    vec3 vec3::cross(const vec3& a)
    {
        return cross(*this, a);
    }

    void vec3::normalize()
    {
        *this = *this / this->length();
    }

    bool vec3::operator==(const vec3& a) const
    {
        return Equal(a.x, x) && Equal(a.y, y) && Equal(a.z, z);
    }

    bool vec3::operator!=(const vec3& a) const
    {
        return !(*this == a);
    }

    vec3& vec3::operator+=(const vec3& a)
    {
        x += a.x;
        y += a.y;
        z += a.z;

        return *this;
    }

    vec3 vec3::operator+(const vec3& a) const
    {
        vec3 r(x + a.x, y + a.y, z + a.z);
        return r;
    }

    vec3& vec3::operator-=(const vec3& a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;

        return *this;
    }

    vec3 vec3::operator-(const vec3& a) const
    {
        vec3 r(x - a.x, y - a.y, z - a.z);
        return r;
    }

    vec3 vec3::operator-() const
    {
        return vec3(-x, -y, -z);
    }

    vec3& vec3::operator*=(float num)
    {
        x *= num;
        y *= num;
        z *= num;

        return *this;
    }

    vec3 vec3::operator*(float num) const
    {
        vec3 r(this->x * num, this->y * num, this->z * num);
        return r;
    }

    vec3& vec3::operator/=(float num)
    {
        x /= num;
        y /= num;
        z /= num;

        return *this;
    }

    vec3 vec3::operator/(float num) const
    {
        vec3 r(this->x / num, this->y / num, this->z / num);

        return r;
    }

    float& vec3::operator[](int i)
    {
        if (i == 0)
        {
            return x;
        }
        else if (i == 1)
        {
            return y;
        }
        else if (i == 2)
        {
            return z;
        }
    }

    vec3 operator*(float num, const vec3& a)
    {
        vec3 r(a.x * num, a.y * num, a.z * num);
        return r;
    }

    Color operator*(const Color& c1, const Color& c2)
    {
        return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    vec4 vec4::zero()
    {
        return vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }

    vec4 vec4::up()
    {
        return vec4(0.0f, 1.0f, 0.0f, 0.0f);
    }

    vec4 vec4::down()
    {
        return vec4(0.0f, -1.0f, 0.0f, 0.0f);
    }

    vec4 vec4::right()
    {
        return vec4(1.0f, 0.0f, 0.0f, 0.0f);
    }

    vec4 vec4::left()
    {
        return vec4(-1.0f, 0.0f, 0.0f, 0.0f);
    }

    vec4 vec4::forward()
    {
        return vec4(0.0f, 0.0f, 1.0f, 0.0f);
    }

    vec4 vec4::back()
    {
        return vec4(0.0f, 0.0f, -1.0f, 0.0f);
    }

    bool vec4::operator==(const vec4& a) const
    {
        return Equal(a.x, x) && Equal(a.y, y) && Equal(a.z, z) && Equal(a.w, w);
    }

    bool vec4::operator!=(const vec4& a) const
    {
        return !(*this == a);
    }

    vec4& vec4::operator+=(const vec4& a)
    {
        x += a.x;
        y += a.y;
        z += a.z;
        w += a.w;

        return *this;
    }

    vec4 vec4::operator+(const vec4& a) const
    {
        vec4 r(x + a.x, y + a.y, z + a.z, w + a.w);
        return r;
    }

    vec4& vec4::operator-=(const vec4& a)
    {
        x -= a.x;
        y -= a.y;
        z -= a.z;
        w -= a.w;

        return *this;
    }

    vec4 vec4::operator-(const vec4& a) const
    {
        vec4 r(x - a.x, y - a.y, z - a.z, w - a.w);
        return r;
    }

    vec4 vec4::operator-() const
    {
        return vec4(-x, -y, -z, -w);
    }

    vec4& vec4::operator*=(float num)
    {
        x *= num;
        y *= num;
        z *= num;
        w *= num;

        return *this;
    }

    vec4 vec4::operator*(float num) const
    {
        vec4 r(this->x * num, this->y * num, this->z * num, this->w * num);
        return r;
    }

    vec4& vec4::operator/=(float num)
    {
        x /= num;
        y /= num;
        z /= num;
        w /= num;

        return *this;
    }

    vec4 vec4::operator/(float num) const
    {
        vec4 r(this->x / num, this->y / num, this->z / num, this->w / num);

        return r;
    }

    float& vec4::operator[](int i)
    {
        if (i == 0)
        {
            return x;
        }
        else if (i == 1)
        {
            return y;
        }
        else if (i == 2)
        {
            return z;
        }
        else if (i == 3)
        {
            return w;
        }
    }

    vec4 operator*(float num, const vec4& a)
    {
        vec4 r(a.x * num, a.y * num, a.z * num, a.w * num);
        return r;
    }

    //////////////////////////////////////////////////////////////////////

    Ray::Ray(const vec3& o, const vec3 dir)
        :
        m_origin(o),
        m_direction(dir)
    {
    }

    vec3 Ray::operator()(float t)
    {
        return m_origin + t * m_direction;
    }
}

