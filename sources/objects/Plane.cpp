#include "objects/Plane.hpp"

Plane::Plane(const Point& position, const Vector& normal)
{
	this->position = position;
	this->normal = normal;
	texture = nullptr;
}

Hit Plane::intersect(const Ray& ray) const
{
	// Compute anglz between ray and plane's normal
	float denom = normal.dot(ray.direction);

	if (abs(denom) > 0.0001f)
	{
		// Compute distance from ray origin to plane
		Vector v = position - ray.origin;
		float t = v.dot(normal) / denom;

		if (t > 0.01f)
			return Hit(t, normal, material.color);
	}

	return Hit::NO_HIT();
}
