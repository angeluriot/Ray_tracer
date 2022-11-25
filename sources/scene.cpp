/**
* Framework for a raytracer
* File: scene.cpp
*
* Created for the Computer Science course "Introduction Computer Graphics"
* taught at the University of Groningen by Tobias Isenberg.
*
* Authors:
* Maarten Everts
* Jasper van de Gronde
*
* This framework is inspired by and uses code of the raytracer framework of
* Bert Freudenberg that can be found at
* http://isgwww.cs.uni-magdeburg.de/graphik/lehre/cg2/projekt/rtprojekt.html
*/

#include "scene.hpp"
#include "material.hpp"

Color Scene::trace(const Ray& ray)
{
	// Find hit object and distance
	Hit min_hit(std::numeric_limits<double>::infinity(),Vector());
	Object* obj = NULL;

	for (unsigned int i = 0; i < objects.size(); ++i)
	{
		Hit hit(objects[i]->intersect(ray));

		if (hit.t < min_hit.t)
		{
			min_hit = hit;
			obj = objects[i];
		}
	}

	// No hit? Return background color.
	if (!obj) return Color(0., 0., 0.);

	Material* material = obj->material;	// The hit objects material
	Point hit = ray.at(min_hit.t);		// The hit point
	Vector N = min_hit.N;				// The normal at hit point
	Vector V = -ray.D;					// The view vector

	/****************************************************
	* This is where you should insert the color
	* calculation (Phong model).
	*
	* Given: material, hit, N, V, lights[]
	* Sought: color
	*
	* Hints: (see triple.h)
	*		Triple.dot(Vector) dot product
	*		Vector+Vector	  vector sum
	*		Vector-Vector	  vector difference
	*		Point-Point		yields vector
	*		Vector.normalize() normalizes vector, returns length
	*		double*Color		scales each color component (r,g,b)
	*		Color*Color		dito
	*		pow(a,b)		   a to the power of b
	****************************************************/

	Color color = material->color;		// place holder

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
