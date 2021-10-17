#include "LRT.h"


namespace LRT
{
	LRT::Color lighting(const Material& mat, const PointLight& light, const LRT::vec3& point, const LRT::vec3& view, const LRT::vec3& normal)
	{
		LRT::Color base_color = mat.color * light.color;

		LRT::vec3 light_dir = (light.position - point).getNormalized();

		LRT::Color ambient = base_color * mat.ambient;

		f32 light_dot_normal = light_dir.dot(normal);

		if (light_dot_normal < 0) return ambient;

		LRT::Color diffuse = base_color * mat.diffuse * light_dot_normal;

		LRT::vec3 reflect = LRT::vec3::reflect(-light_dir, normal);
		f32 reflect_dot_view = reflect.dot(view);

		if (reflect_dot_view <= 0) return ambient + diffuse;

		f32 factor = std::pow(reflect_dot_view, mat.shininess);
		LRT::Color specular = light.color * mat.specular * factor;

		return ambient + diffuse + specular;
	}

	PreComputedValues::PreComputedValues(const Intersection& i, const Ray& ray)
		:
		intersection(i),
		point(ray(i.t)),
		view(-ray.direction),
		normal(i.obj->normalAt(point))
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
	}

	Color LRTAPI shadeHit(World& w, const PreComputedValues& comps)
	{
		Color c(0.0f, 0.0f, 0.0f);

		for (auto& light : w.lights)
		{
			LRT::vec3 dir = (light.position - comps.point).getNormalized();

			Ray shadow_ray(comps.point + 0.01f * comps.normal, dir);
			std::vector<Intersection> hits = intersect(shadow_ray, w);
			u32 h = hit(hits);
			
			if (h == -1)
			{
				c += lighting(comps.intersection.obj->material, light, comps.point, comps.view, comps.normal);
			}
			else
			{
				c += comps.intersection.obj->material.color * light.color * comps.intersection.obj->material.ambient;
			}
			
		}

		return c;
	}

	Color color_at(World& w, const Ray ray)
	{
		std::vector<Intersection> inters = intersect(ray, w);
		u32 i = hit(inters);

		if (i == -1)
		{
			return LRT::Colors::black;
		}

		return shadeHit(w, PreComputedValues(inters[i], ray));
	}

	Canvas Render(const Camera& cam, World& w)
	{
		Canvas image(cam.Width(), cam.Height());

		for (u32 y = 0; y < cam.Height(); y++)
		{
			for (u32 x = 0; x < cam.Width(); x++)
			{
				Ray r = cam.RayForPixel(x, y);
				Color c = color_at(w, r);
				image.SetPixel(x, y, c);
			}
		}

		return image;
	}
}
