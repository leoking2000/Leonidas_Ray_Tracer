#include "LRT.h"
#include <limits>
#include <iterator>
#include <algorithm>

namespace LRT
{
	constexpr f32 EPSILON = 0.01f;

	Canvas Render(const Camera& cam, World& w)
	{
		Canvas image(cam.Width(), cam.Height());

		for (u32 y = 0; y < cam.Height(); y++)
		{
			for (u32 x = 0; x < cam.Width(); x++)
			{
				Ray r = cam.RayForPixel(x, y);
				Color c = color_at(w, r, 15);
				image.SetPixel(x, y, c);
			}
		}

		return image;
	}

	Color color_at(World& w, const Ray ray, u32 limit)
	{
		std::vector<Intersection> inters = intersect(ray, w);
		u32 i = hit(inters);

		if (i == -1)
		{
			return LRT::Colors::black;
		}

		return shadeHit(PreComputedValues(inters[i], ray, w), limit);
	}

	Color  shadeHit(const PreComputedValues& comps, u32 limit)
	{
		Color c(0.0f, 0.0f, 0.0f);

		for (auto& light : comps.world.lights)
		{
			bool inShadow = isShadowed(comps.world, light.position, comps.point + EPSILON * comps.normal);

			u32 id = comps.intersection.shapeID;

			Color light_color = lighting(*comps.world.objects[id],
				light, comps.point, comps.view, comps.normal, inShadow);

			Color reflection_color = Reflected_color(comps, comps.world, limit);

			c += light_color + reflection_color;
		}

		return c;
	}

	Color Reflected_color(const PreComputedValues& comps, World& w, u32 limit)
	{
		f32 reflect = w.objects[comps.intersection.shapeID]->GetMaterial().reflective;

		if (LRT::Equal(reflect, 0.0f) || limit == 0)
		{
			return LRT::Colors::black;
		}

		LRT::Ray reflect_ray(comps.point + EPSILON * comps.normal, comps.reflectv);
		LRT::Color c = color_at(w, reflect_ray, limit - 1);

		return c * reflect;
	}

	LRT::Color lighting(const Shape& obj, const PointLight& light, const vec3& point, const vec3& view, const vec3& normal, bool inShadow)
	{
		const Material& mat = obj.GetMaterial();

		Color base_color = mat.colorAt(point, obj.GetInverseModelMatrix()) * light.color;

		Color ambient = base_color * mat.ambient;
		if (inShadow) return ambient;

		vec3 light_dir = (light.position - point).getNormalized();

		f32 light_dot_normal = light_dir.dot(normal);

		if (light_dot_normal < 0) return ambient;

		Color diffuse = base_color * mat.diffuse * light_dot_normal;

		vec3 reflect = LRT::vec3::reflect(-light_dir, normal);
		f32 reflect_dot_view = reflect.dot(view);

		if (reflect_dot_view <= 0) return ambient + diffuse;

		f32 factor = std::pow(reflect_dot_view, mat.shininess);
		Color specular = light.color * mat.specular * factor;

		return ambient + diffuse + specular;
	}

	PreComputedValues::PreComputedValues(const Intersection& i, const Ray& ray, World& w)
		:
		world(w),
		intersection(i),
		point(ray(i.t)),
		view(-ray.direction),
		normal(w.objects[i.shapeID]->normalAt(point))
	{
		if (LRT::vec3::dot(normal, view) < 0)
		{
			isInside = true;
			normal = -normal;
		}
		else
		{
			isInside = false;
		}

		reflectv = LRT::vec3::reflect(ray.direction, normal);
	}

	std::vector<Intersection> intersect(const Ray& ray, World& w)
	{
		std::vector<Intersection> intersections;

		for (u32 i = 0; i < w.objects.size(); i++)
		{
			std::vector<Intersection> inter = w.objects[i]->intersect(ray);
			std::copy(inter.begin(), inter.end(), std::back_inserter(intersections));
		}

		std::sort(intersections.begin(), intersections.end(),
			[](const Intersection& i1, const Intersection& i2) { return i1.t < i2.t; });

		return intersections;
	}

	u32  hit(const std::vector<Intersection>& intersections)
	{
		u32 currHitIndex = -1;
		f32 min_t = std::numeric_limits<float>::max();

		for (u32 i = 0; i < intersections.size(); i++)
		{
			f32 t = intersections[i].t;

			if (t <= 0)
			{
				continue;
			}
			else if (t < min_t)
			{
				min_t = t;
				currHitIndex = i;
			}
		}

		return currHitIndex;
	}

	bool  isShadowed(World& w, const vec3 lightPos, const vec3 point)
	{
		vec3 ptl = lightPos - point; // point to light

		f32 distance = ptl.length();
		vec3 direction = ptl.getNormalized();

		Ray shadow_ray(point, direction);
		std::vector<Intersection> hits = intersect(shadow_ray, w);
		u32 h = hit(hits);

		if (h == -1)
		{
			return false; // no Intersection
		}

		if (hits[h].t >= distance)
		{
			return false;
		}

		return true;
	}
}
