#include "LRT.h"
#include <limits>
#include <iterator>
#include <algorithm>
#include <iostream>

namespace LRT
{
	constexpr f32 EPSILON = 0.01f;

	Canvas Render(const Camera& cam, World& w, u32 limit)
	{
		Canvas image(cam.Width(), cam.Height());

		for (u32 y = 0; y < cam.Height(); y++)
		{
			std::cout << "Scan line remaining " << cam.Height() - y << "\n";
			for (u32 x = 0; x < cam.Width(); x++)
			{
				Ray r = cam.RayForPixel(x, y);
				Color c = color_at(w, r, limit);
				image.SetPixel(x, y, c);
			}
		}
		std::cout << "Rendering Done\n";
		return image;
	}

	Color color_at(World& w, const Ray ray, u32 limit)
	{
		std::vector<Intersection> inters = intersect(ray, w);
		u32 i = hit(inters);

		if (i == -1)
		{
			return Colors::black;
		}

		return shadeHit(PreComputedValues(inters[i], ray, w), limit);
	}

	Color  shadeHit(const PreComputedValues& comps, u32 limit)
	{
		Color c(0.0f, 0.0f, 0.0f);

		for (auto& light : comps.world.lights)
		{
			bool inShadow = isShadowed(comps.world, light.position, comps.point + EPSILON * comps.normal);

			u64 id = comps.intersection.GetPrimitiveID();

			Color light_color = lighting(*comps.world.objects[id],
				light, comps.point, comps.view, comps.normal, inShadow);

			float reflect = comps.world.objects[comps.intersection.GetPrimitiveID()]->GetMaterial().reflective;

			Color reflection_color = Reflected_color(comps, comps.world, limit);

			c += (1 - reflect) * light_color + reflection_color;
		}

		return c;
	}

	Color Reflected_color(const PreComputedValues& comps, World& w, u32 limit)
	{
		float reflect = w.objects[comps.intersection.GetPrimitiveID()]->GetMaterial().reflective;

		if (glm::epsilonEqual(reflect, 0.0f, 0.00001f) || limit == 0)
		{
			return Colors::black;
		}

		LRT::Ray reflect_ray(comps.point + EPSILON * comps.normal, comps.reflectv);
		Color c = color_at(w, reflect_ray, limit - 1);

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

	PreComputedValues::PreComputedValues(const Intersection& i, const Ray& ray, World& w)
		:
		world(w),
		intersection(i),
		point(ray(i.GetDistance())),
		view(-ray.direction),
		normal(w.objects[i.GetPrimitiveID()]->normalAt(point))
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

	std::vector<Intersection> intersect(const Ray& ray, World& w)
	{
		std::vector<Intersection> intersections;

		for (u32 i = 0; i < w.objects.size(); i++)
		{
			std::vector<Intersection> inter = w.objects[i]->intersect(ray);
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

	bool  isShadowed(World& w, const glm::vec3 lightPos, const glm::vec3 point)
	{
		glm::vec3 ptl = lightPos - point; // point to light

		f32 distance = glm::length(ptl);
		glm::vec3 direction = glm::normalize(ptl);

		Ray shadow_ray(point, direction);
		std::vector<Intersection> hits = intersect(shadow_ray, w);
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
