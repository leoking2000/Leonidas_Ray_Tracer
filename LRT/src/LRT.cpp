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
	Color LRTAPI shadeHit(const World& w, const PreComputedValues& comps)
	{
		Color c(0.0f, 0.0f, 0.0f);

		for (auto& light : w.lights)
		{
			c += lighting(comps.intersection.obj.material, light, comps.point, comps.view, comps.normal);
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
}
