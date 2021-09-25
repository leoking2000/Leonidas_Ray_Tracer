#include "graphics.h"


namespace LRT
{
	PointLight::PointLight(const vec3& pos, const Color& c)
		:
		position(pos),
		color(c)
	{
	}

	///////////////////////////////////////////////////////////////

	LRT::Color lighting(const Material& mat, const PointLight& light, const LRT::vec3& point, const LRT::vec3& view, const LRT::vec3& normal)
	{
		LRT::Color base_color = mat.color * light.color;

		LRT::vec3 light_dir = (light.position - point).getNormalized();

		LRT::Color ambient = base_color * mat.ambient;

		float light_dot_normal = light_dir.dot(normal);

		if (light_dot_normal < 0) return ambient;

		LRT::Color diffuse = base_color * mat.diffuse * light_dot_normal;

		LRT::vec3 reflect = LRT::vec3::reflect(-light_dir, normal);
		float reflect_dot_view = reflect.dot(view);

		if (reflect_dot_view <= 0) return ambient + diffuse;

		float factor = std::pow(reflect_dot_view, mat.shininess);
		LRT::Color specular = light.color * mat.specular * factor;


		return ambient + diffuse + specular;
	}

}

