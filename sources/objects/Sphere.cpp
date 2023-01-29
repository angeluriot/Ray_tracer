#include "objects/Sphere.hpp"

Hit Sphere::intersect(const Ray& ray) const
{
	// The vector from the ray origin to the sphere center
	Vector OC = position - ray.origin;
	// The closest distance from the ray origin to the sphere
	float t = OC.dot(ray.direction);

	// The closest point on the ray to the sphere center
	Vector closest = ray.at(t);

	// If the closest point is outside the sphere, there is no intersection
	if ((closest - position).length() > radius)
		return Hit::NO_HIT();

	// The distance from the closest point to the sphere center
	float y = (position - closest).length();
	// The distance from the closest point to the intersection points
	float x = sqrt(radius * radius - y * y);
	// The distance from the ray origin to the first intersection point
	float distance = t - x;

	if (distance < 0.01f)
	{
		if (t + x < 0.01f)
			return Hit::NO_HIT();

		// Inside the sphere
		distance = t + x;
	}

	// The first intersection point
	Point intersection = ray.at(distance);
	// The normal at the first intersection point
	Vector normal = (intersection - position).normalized();

	return Hit(distance, normal);
}

void Sphere::compute_texture() const
{
	
}
