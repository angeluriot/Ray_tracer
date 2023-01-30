#include "objects/Sphere.hpp"


constexpr float PI = 3.141592653589793f;

Sphere::Sphere(const Point& position, float radius)
{
	this->position = position;
	this->radius = radius;
	texture = nullptr;
}

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

	if (!texture)
		return Hit(distance, normal, material.color);

	Vector north = Vector(0.f, 1.f, 0.f);
	Vector start = Vector(0.f, 0.f, 1.f);

	// Normal is a point that we project onto the plane defined by the north vector
	Vector equator_point = normal - north * normal.dot(north);

	float u = 0.5f + atan(equator_point.dot(start)) / (2.f * PI);
	float v = acos(normal.dot(north)) / PI;
	Color color = texture->colorAt(u, v);

	return Hit(distance, normal, color);
}
