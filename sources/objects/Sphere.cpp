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

	if (!texture && !normals && !specular)
		return Hit(distance, normal, material.color);

	// Project the normal onto the plane defined by the north vector
	Vector projected_3d = normal.dot(north) * north / north.length_2();
	Vector projected_3d_plane = normal - projected_3d;
	float projected_2d_x = projected_3d_plane.dot(start);
	float projected_2d_y = projected_3d_plane.dot(north.cross(start));

	// Calculate the texture coordinates
	float u = 1.f - (0.5f + atan2(projected_2d_x, projected_2d_y) / (2.f * PI));
	float v = acos(normal.dot(north)) / PI;

	Color color = texture ? texture->colorAt(u, v) : material.color;
	float specular_strength = specular ? specular->colorAt(u, v).r : 1.f;

	if (!normals)
		return Hit(distance, normal, color, specular_strength);

	float normal_theta = acos(normal.z);
	float normal_phi = (normal.y < 0.f ? -1.f : 1.f) * acos(normal.x / (sqrt(normal.x * normal.x + normal.y * normal.y) + 0.00001f));

	Vector change = ((normals->colorAt(u, v) * 2.f) - 1.f).normalized();
	float change_theta = acos(change.z);
	float change_phi = (change.y < 0.f ? -1.f : 1.f) * acos(change.x / (sqrt(change.x * change.x + change.y * change.y) + 0.00001f));

	normal_theta += change_theta * 0.3f;
	normal_phi += change_phi * 0.3f;

	normal = Vector(sin(normal_theta) * cos(normal_phi), sin(normal_theta) * sin(normal_phi), cos(normal_theta)).normalized();

	return Hit(distance, normal, color, specular_strength);
}
