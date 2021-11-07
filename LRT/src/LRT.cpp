#include "LRT.h"


namespace LRT
{
	LRT::Color lighting(const Material& mat, const PointLight& light, const LRT::vec3& point, const LRT::vec3& view, const LRT::vec3& normal, bool inShadow)
	{
		LRT::Color base_color = mat.color * light.color;

		LRT::Color ambient = base_color * mat.ambient;
		if (inShadow) return ambient;

		LRT::vec3 light_dir = (light.position - point).getNormalized();

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
	}

	Color LRTAPI shadeHit(const PreComputedValues& comps)
	{
		Color c(0.0f, 0.0f, 0.0f);

		constexpr f32 EPSILON = 0.01f;

		for (auto& light : comps.world.lights)
		{
			bool inShadow = isShadowed(comps.world, light.position, comps.point + EPSILON * comps.normal);

			u32 id = comps.intersection.shapeID;

			c += lighting(comps.world.objects[id]->material,
				light, comps.point, comps.view, comps.normal,inShadow);
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

		return shadeHit(PreComputedValues(inters[i], ray, w));
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
