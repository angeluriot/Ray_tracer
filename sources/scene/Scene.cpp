#include <algorithm>
#include "light/Hit.hpp"
#include "scene/Scene.hpp"
#include "utils/Material.hpp"

Ray get_refracted_ray(Point hit, Ray ray, Vector normal, float n_1, float n_2)
{
	float n = n_1 / n_2;
	float cos_incident = -normal.dot(ray.direction);
	float sin_t2 = n * n * (1.f - cos_incident * cos_incident);

	// Total internal reflection
	if (sin_t2 > 1.f)
	{
		Vector reflect = 2.f * (normal.dot(-ray.direction)) * normal + ray.direction;
		return Ray(hit, reflect);
	}

	// Refraction
	float cos_t = sqrt(1.f - sin_t2);
	Vector direction = n * ray.direction + (n * cos_incident - cos_t) * normal;
	return Ray(hit, direction);
}

Color Scene::trace(const Ray& ray, int depth)
{
	// Find hit object and distance
	Hit min_hit(std::numeric_limits<float>::infinity(), Vector(), Color());
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
		// Compute refraction
		if (material.refractive_index > 0.f && depth < recursions)
		{
			Ray new_ray;
			Color specular(0.f, 0.f, 0.f);

			if (ray.direction.dot(normal) < 0.f)
			{
				new_ray = get_refracted_ray(hit, ray, normal, 1.f, material.refractive_index);

				// Specular reflection
				for (int i = 0; i < lights.size(); i++)
				{
					Vector light_dir = (lights[i].position - hit).normalized();
					Vector reflect = 2.f * (normal.dot(light_dir)) * normal - light_dir;
					color += material.specular * lights[i].color * pow(std::max(0.f, reflect.dot(view_dir)), material.shininess);
				}
			}

			else
				new_ray = get_refracted_ray(hit, ray, -normal, material.refractive_index, 1.f);

			return trace(new_ray, depth + 1) + color;
		}

		// For all lights in the scene
		for (int i = 0; i < lights.size(); i++)
		{
			float is_shadowed = 0.f;

			// The vector from the hit point to the light source
			Vector light_vector = lights[i].position - hit;
			Vector light_dir = light_vector.normalized();

			// Compute shadows
			if (shadows_on)
			{
				if (soft_shadows == 0)
				{
					Ray reverse_ray(hit, light_dir);
						double hit_distance = light_vector.length();

						// For all objects in the scene
						for (int k = 0; k < objects.size(); k++)
							if (!(k == obj_index))
							{
								Hit reverse_hit(objects[k]->intersect(reverse_ray));

								if (!reverse_hit.no_hit && reverse_hit.distance < hit_distance && reverse_hit.distance > 0.001f)
								{
									is_shadowed = 1.f;
									break;
								}
							}
				}

				else
					for (int i = -soft_shadows; i < soft_shadows; i++)
					{
						for (int j = -soft_shadows; j < soft_shadows; j++)
						{
							Ray reverse_ray(hit, Vector(light_dir.x + i * 0.002f + j * 0.002f, light_dir.y + i * 0.002f + j * 0.002f, light_dir.z + i * 0.002f + j * 0.002f));
							double hit_distance = light_vector.length();

							// For all objects in the scene
							for (int k = 0; k < objects.size(); k++)
								if (!(k == obj_index))
								{
									Hit reverse_hit(objects[k]->intersect(reverse_ray));

									if (!reverse_hit.no_hit && reverse_hit.distance < hit_distance && reverse_hit.distance > 0.001f)
									{
										is_shadowed++;
										break;
									}
								}
						}
					}
			}

			if (!gooch)
			{
				is_shadowed /= (float)((1 + 2 * soft_shadows) * (1 + 2 * soft_shadows));
				float enlightenment = 1.f - is_shadowed;

				// Add ambient light
				color += min_hit.color * material.ambient * lights[i].color;

				// Add diffuse light
				color += min_hit.color * enlightenment * material.diffuse * lights[i].color * std::max(0.f, normal.dot(light_dir));
				// The direction of the reflected ray
				Vector reflect = 2.f * (normal.dot(light_dir)) * normal - light_dir;
				// Add specular light
				color += material.specular * enlightenment * lights[i].color * pow(std::max(0.f, reflect.dot(view_dir)), material.shininess);

				// If not shadowed
				//if (!is_shadowed)
				//{
					// Add diffuse light
					//color += min_hit.color * material.diffuse * lights[i].color * std::max(0.f, normal.dot(light_dir));
					// The direction of the reflected ray
					//Vector reflect = 2.f * (normal.dot(light_dir)) * normal - light_dir;
					// Add specular light
					//color += material.specular * lights[i].color * pow(std::max(0.f, reflect.dot(view_dir)), material.shininess);
				//}
			}

			else
			{
				Vector k_b = Vector(0.f, 0.f, b);
				Vector k_y = Vector(y, y, 0.f);
				Vector k_cool = k_b + alpha * lights[i].color * min_hit.color * material.diffuse;
				Vector k_warm = k_y + beta  * lights[i].color * min_hit.color * material.diffuse;
				Vector i_gooch = k_cool * (1.f - normal.dot(light_dir)) / 2.f + k_warm * (1.f + normal.dot(light_dir)) / 2.f;

				color += i_gooch;

				// The direction of the reflected ray
				Vector reflect = 2.f * (normal.dot(light_dir)) * normal - light_dir;
				// Add specular light
				color += material.specular * lights[i].color * pow(std::max(0.f, reflect.dot(view_dir)), material.shininess);
			}
		}

		if (!gooch)
		{
			// Reflection
			if (depth < recursions && material.specular > 0.f)
			{
				Vector reflect = 2.f * (normal.dot(view_dir)) * normal - view_dir;
				Ray reflected_ray(hit, reflect);
				Color reflected_color = trace(reflected_ray, depth + 1);
				color += material.specular * reflected_color;
			}
		}
	}

	return color;
}

void Scene::render(Image& image)
{
	float w = float(image.width());
	float h = float(image.height());
	float mean = (w + h) / 2.f;
	Vector position = camera.position;
	Vector direction = camera.direction;
	Vector up = camera.up;
	Vector right = camera.direction.cross(camera.up);
	float fov = 0.4f;

	// Loop over all pixels
	for (int y = 0; y < image.height(); y++)
		for (int x = 0; x < image.width(); x++)
		{
			std::vector<Color> colors;

			// Antialiasing
			for (float i = 0.f; i < 1.f; i += 1.f / float(antialiasing))
				for (float j = 0.f; j < 1.f; j += 1.f / float(antialiasing))
				{
					Point pixel = position + direction + right * ((float(x + i) - w / 2.f) / mean) * fov - up * ((float(y + j) - h / 2.f) / mean) * fov;
					Ray ray(camera.position, (pixel - camera.position).normalized());
					Color col = trace(ray);
					col.clamp();
					colors.push_back(col);
				}

			Color color(0.f, 0.f, 0.f);

			// Average colors
			for (Color& col : colors)
				color += col / float(colors.size());

			image(x, y) = color;
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

void Scene::set_mode(const std::string& mode)
{
	if (mode == "default")
		this->mode = Mode::Default;
	else if (mode == "normals")
		this->mode = Mode::Normals;
	else if (mode == "z-buffer")
		this->mode = Mode::ZBuffer;
}

unsigned int Scene::get_nb_objects()
{
	return objects.size();
}

unsigned int Scene::get_nb_lights()
{
	return lights.size();
}
