#include "objects/Plane.hpp"

Hit Plane::intersect(const Ray& ray)
{
	// Compute anglz between ray and plane's normal
	double denom = normal.dot(ray.direction);

	if (abs(denom) > 10e-8)
	{
		// Compute distance from ray origin to plane
		Vector v = position - ray.origin;
		double t = v.dot(normal) / denom;

		if (t >= 0)
			return Hit(t, normal);
	}

	return Hit::NO_HIT();
}
