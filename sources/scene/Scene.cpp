#include <algorithm>
#include "light/Hit.hpp"
#include "scene/Scene.hpp"
#include "utils/Material.hpp"

Color Scene::trace(const Ray& ray)
{
	// Find hit object and distance
	Hit min_hit(std::numeric_limits<float>::infinity(), Vector());
	Object* obj = nullptr;
	int obj_index;

	for (int i = 0; i < objects.size(); i++)
	{
		Hit hit(objects[i]->intersect(ray));

		if (hit.distance < min_hit.distance)
		{
			min_hit = hit;
			obj = objects[i];
			obj_index = i;
		}
	}

	// No hit? Return background color.
	if (!obj)
		return Color(0.f, 0.f, 0.f);

	Material material = obj->material;		// The hit objects material
	Point hit = ray.at(min_hit.distance);	// The hit point
	Vector normal = min_hit.normal;			// The normal at hit point
	Vector view_dir = -ray.direction;		// The view vector

	Color color = Color(0.f, 0.f, 0.f);

	if (mode == Mode::Normals)
		color = (normal + 1.f) / 2.f;

	else if (mode == Mode::ZBuffer)
	{
		float zbuffer_value = std::clamp(1.f - ((min_hit.distance - near) / (far - near)), 0.f, 1.f);
		color = Color(zbuffer_value, zbuffer_value, zbuffer_value);
	}

	else
	{
		// For all lights in the scene
		for (int i = 0; i < lights.size(); i++)
		{
			// The vector from the hit point to the light source
			Vector light_vector = lights[i].position - hit;
			Vector light_dir = light_vector.normalized();

			Ray reverse_ray(hit, light_dir);

			bool is_shadowed = false;

			if (shadows_on)
			{
				double hit_distance = light_vector.length();

				for (int j = 0; j < objects.size(); j++)
				{
					if (!(j == obj_index))
					{
						Hit reverse_hit(objects[j]->intersect(reverse_ray));

						if (!reverse_hit.no_hit && reverse_hit.distance < hit_distance && reverse_hit.distance > 0.001f)
						{
							is_shadowed = true;
							break;
						}
					}
				}
			}

			// The direction of the reflected ray
			Vector reflect = 2.f * (normal.dot(light_dir)) * normal - light_dir;

			// Add ambient light
			color += material.color * material.ambient * lights[i].color;

			if (!(shadows_on && is_shadowed))
			{
				// Add diffuse light
				color += material.color * material.diffuse * lights[i].color * std::max(0.f, normal.dot(light_dir));
				// Add specular light
				color += material.specular * lights[i].color * pow(std::max(0.f, reflect.dot(view_dir)), material.shininess);
			}
		}
	}

	return color;
}

void Scene::render(Image& image)
{
	int w = image.width();
	int h = image.height();

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			Point pixel(x + 0.5f, h - 1.f - y + 0.5f, 0.f);
			Ray ray(eye, (pixel - eye).normalized());
			Color col = trace(ray);
			col.clamp();
			image(x, y) = col;
		}
}

void Scene::add_object(Object* object)
{
	objects.push_back(object);
}

void Scene::add_light(const Light& light)
{
	lights.push_back(light);
}

void Scene::set_eye(Point eye)
{
	this->eye = eye;
}

void Scene::set_mode(const std::string& mode)
{
	if (mode == "default")
		this->mode = Mode::Default;
	else if (mode == "normals")
		this->mode = Mode::Normals;
	else if (mode == "z-buffer")
		this->mode = Mode::ZBuffer;
}

void Scene::set_distances(float near, float far)
{
	this->near = near;
	this->far = far;
}

void Scene::set_shadows(bool shadows_on)
{
	this->shadows_on = shadows_on;
}

Scene::Mode Scene::get_mode()
{
	return mode;
}

unsigned int Scene::get_nb_objects()
{
	return objects.size();
}

unsigned int Scene::get_nb_lights()
{
	return lights.size();
}
