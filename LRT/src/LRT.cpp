#include "LRT.h"
#include <limits>
#include <iterator>
#include <algorithm>
//#include <iostream>

namespace LRT
{
	constexpr f32 EPSILON = 0.01f;

	Canvas Render(const Camera& cam, Scene& s, u32 limit)
	{
		Canvas image(cam.Width(), cam.Height());

		for (u32 y = 0; y < cam.Height(); y++)
		{
			//std::cout << "Scan line remaining " << cam.Height() - y << "\n";
			for (u32 x = 0; x < cam.Width(); x++)
			{
				Ray r = cam.RayForPixel(x, y);
				Color c = color_at(s, r, limit);
				image.SetPixel(x, y, c);
			}
		}
		//std::cout << "Rendering Done\n";
		return image;
	}

	Color color_at(Scene& s, const Ray ray, u32 limit)
	{
		std::vector<Intersection> inters = intersect(ray, s);
		u32 i = hit(inters);

		if (i == -1)
		{
			glm::vec3 t = glm::vec3(0.5f) * (glm::vec3(ray.direction.y) + glm::vec3(1.0f));
			return (glm::vec3(1.0f) - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
		}

		return shadeHit(PreComputedValues(inters[i], ray, s), limit);
	}

	Color  shadeHit(const PreComputedValues& comps, u32 limit)
	{
		Color c(0.0f, 0.0f, 0.0f);

		for (u32 i = 0; i < comps.scene.NumberOfLight(); i++)
		{
			PointLight& light = comps.scene.GetLight(i);

			bool inShadow = isShadowed(comps.scene, light.position, comps.point + EPSILON * comps.normal);

			u64 id = comps.intersection.GetPrimitiveID();

			Color light_color = lighting(comps.scene.GetObject(id),
				light, comps.point, comps.view, comps.normal, inShadow);

			float reflect = comps.scene.GetObject(comps.intersection.GetPrimitiveID()).GetMaterial().reflective;

			Color reflection_color = Reflected_color(comps, comps.scene, limit);

			c += (1 - reflect) * light_color + reflection_color;
		}

		return c;
	}

	Color Reflected_color(const PreComputedValues& comps, Scene& s, u32 limit)
	{
		float reflect = s.GetObject(comps.intersection.GetPrimitiveID()).GetMaterial().reflective;

		if (glm::epsilonEqual(reflect, 0.0f, 0.00001f) || limit == 0)
		{
			return Colors::black;
		}

		LRT::Ray reflect_ray(comps.point + EPSILON * comps.normal, comps.reflectv);
		Color c = color_at(s, reflect_ray, limit - 1);

		return c * reflect;
	}

	Color lighting(
		const Primitive& obj, 
		const PointLight& light, 
		const glm::vec3& point, 
		const glm::vec3& view, 
		const glm::vec3& normal, 
		bool inShadow)
	{
		const Material& mat = obj.GetMaterial();

		Color base_color = mat.colorAt(point, obj.transform.WorldToLocal()) * light.color;

		Color ambient = base_color * mat.ambient;
		if (inShadow) return ambient;

		glm::vec3 light_dir = glm::normalize(light.position - point);

		f32 light_dot_normal = glm::dot(light_dir,normal);

		if (light_dot_normal < 0) return ambient;

		Color diffuse = base_color * mat.diffuse * light_dot_normal;

		glm::vec3 reflect = glm::reflect(-light_dir, normal);
		f32 reflect_dot_view = glm::dot(reflect,view);

		if (reflect_dot_view <= 0) return ambient + diffuse;

		f32 factor = std::pow(reflect_dot_view, mat.shininess);
		Color specular = light.color * mat.specular * factor;

		return ambient + diffuse + specular;
	}

	PreComputedValues::PreComputedValues(const Intersection& i, const Ray& ray, Scene& s)
		:
		scene(s),
		intersection(i),
		point(ray(i.GetDistance())),
		view(-ray.direction),
		normal(s.GetObject(i.GetPrimitiveID()).normalAt(point))
	{
		if (glm::dot(normal, view) < 0)
		{
			isInside = true;
			normal = -normal;
		}
		else
		{
			isInside = false;
		}

		reflectv = glm::reflect(ray.direction, normal);
	}

	std::vector<Intersection> intersect(const Ray& ray, Scene& s)
	{
		std::vector<Intersection> intersections;

		for (u32 i = 0; i < s.NumberOfObjects(); i++)
		{
			std::vector<Intersection> inter = s.GetObject(i).intersect(ray);
			std::copy(inter.begin(), inter.end(), std::back_inserter(intersections));
		}

		std::sort(intersections.begin(), intersections.end(),
			[](const Intersection& i1, const Intersection& i2) { return i1.GetDistance() < i2.GetDistance(); });

		return intersections;
	}

	u32  hit(const std::vector<Intersection>& intersections)
	{
		u32 currHitIndex = -1;
		f32 min_t = std::numeric_limits<float>::max();

		for (u32 i = 0; i < intersections.size(); i++)
		{
			f32 t = intersections[i].GetDistance();

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

	bool  isShadowed(Scene& s, const glm::vec3 lightPos, const glm::vec3 point)
	{
		glm::vec3 ptl = lightPos - point; // point to light

		f32 distance = glm::length(ptl);
		glm::vec3 direction = glm::normalize(ptl);

		Ray shadow_ray(point, direction);
		std::vector<Intersection> hits = intersect(shadow_ray, s);
		u32 h = hit(hits);

		if (h == -1)
		{
			return false; // no Intersection
		}

		if (hits[h].GetDistance() >= distance)
		{
			return false;
		}

		return true;
	}
}
