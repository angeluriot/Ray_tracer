#include "light/Hit.hpp"
#include "scene/Scene.hpp"
#include "utils/Material.hpp"

Color Scene::trace(const Ray& ray)
{
	// Find hit object and distance
	Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
	Object* obj = NULL;

	for (unsigned int i = 0; i < objects.size(); ++i)
	{
		Hit hit(objects[i]->intersect(ray));

		if (hit.distance < min_hit.distance)
		{
			min_hit = hit;
			obj = objects[i];
		}
	}

	// No hit? Return background color.
	if (!obj)
		return Color(0., 0., 0.);

	Material material = *(obj->material);	// The hit objects material
	Point hit = ray.at(min_hit.distance);	// The hit point
	Vector normal = min_hit.normal;			// The normal at hit point
	Vector view_dir = -ray.direction;		// The view vector

	Color color = Color(0., 0., 0.);

	if (getMode() == Mode::Normals)
		color = (normal + 1.) / 2.;

	else
	{
		// For all lights in the scene
		for (unsigned int i = 0; i < lights.size(); ++i)
		{
			// The vector from the hit point to the light source
			Vector light_dir = (lights[i]->position - hit).normalized();
			// The direction of the reflected ray
			Vector reflect = 2. * (normal.dot(light_dir)) * normal - light_dir;

			// Add ambient light
			color += material.color * material.ka * lights[i]->color;
			// Add diffuse light
			color += material.color * material.kd * lights[i]->color * std::max(0., normal.dot(light_dir));
			// Add specular light
			color += material.ks * lights[i]->color * pow(std::max(0., reflect.dot(view_dir)), material.n);
		}
	}

	return color;
}

void Scene::render(Image& img)
{
	int w = img.width();
	int h = img.height();

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			Point pixel(x + 0.5, h - 1 - y + 0.5, 0);
			Ray ray(eye, (pixel - eye).normalized());
			Color col = trace(ray);
			col.clamp();
			img(x, y) = col;
		}
}

void Scene::addObject(Object* o)
{
	objects.push_back(o);
}

void Scene::addLight(Light* l)
{
	lights.push_back(l);
}

void Scene::setEye(Triple e)
{
	eye = e;
}
