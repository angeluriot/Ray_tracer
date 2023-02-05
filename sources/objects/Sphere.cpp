#include "objects/Sphere.hpp"


constexpr float PI = 3.141592653589793f;

Sphere::Sphere(const Point& position, float radius, const Vector& north, const Vector& start)
{
	this->position = position;
	this->radius = radius;
	this->north = north.normalized();
	this->start = start.normalized();
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

	// Project the normal onto the plane defined by the north vector
	Vector projected_3d = normal.dot(north) * north / north.length_2();
	Vector projected_3d_plane = normal - projected_3d;
	float projected_2d_x = projected_3d_plane.dot(start);
	float projected_2d_y = projected_3d_plane.dot(north.cross(start));

	// Calculate the texture coordinates
	float u = 1.f - (0.5f + atan2(projected_2d_x, projected_2d_y) / (2.f * PI));
	float v = acos(normal.dot(north)) / PI;

	Color color = texture->colorAt(u, v);

	return Hit(distance, normal, color);
}
