#include "objects/meshs/Cube.hpp"

Cube::Cube(Point position, double size, double pitch, double yaw, double roll)
{
	// Create the 12 triangles of the cube
	triangles[0] = Triangle(Point(0., 0., 0.), Point(0., 0., 1.), Point(0., 1., 0.));
	triangles[1] = Triangle(Point(0., 0., 1.), Point(0., 1., 1.), Point(0., 1., 0.));
	triangles[2] = Triangle(Point(1., 0., 1.), Point(1., 0., 0.), Point(1., 1., 0.));
	triangles[3] = Triangle(Point(1., 1., 1.), Point(1., 0., 1.), Point(1., 1., 0.));
	triangles[4] = Triangle(Point(0., 0., 1.), Point(0., 0., 0.), Point(1., 0., 0.));
	triangles[5] = Triangle(Point(1., 0., 1.), Point(0., 0., 1.), Point(1., 0., 0.));
	triangles[6] = Triangle(Point(0., 1., 0.), Point(0., 1., 1.), Point(1., 1., 0.));
	triangles[7] = Triangle(Point(0., 1., 1.), Point(1., 1., 1.), Point(1., 1., 0.));
	triangles[8] = Triangle(Point(0., 0., 0.), Point(0., 1., 0.), Point(1., 0., 0.));
	triangles[9] = Triangle(Point(0., 1., 0.), Point(1., 1., 0.), Point(1., 0., 0.));
	triangles[10] = Triangle(Point(0., 1., 1.), Point(0., 0., 1.), Point(1., 0., 1.));
	triangles[11] = Triangle(Point(1., 1., 1.), Point(0., 1., 1.), Point(1., 0., 1.));

	// Apply scale
	for (auto& triangle : triangles)
	{
		triangle.point_1 = (triangle.point_1 - 0.5) * size;
		triangle.point_2 = (triangle.point_2 - 0.5) * size;
		triangle.point_3 = (triangle.point_3 - 0.5) * size;
	}

	for (auto& triangle : triangles)
	{
		// Apply pitch
		triangle.point_1 = Point(
			triangle.point_1.x,
			triangle.point_1.y * cos(pitch) - triangle.point_1.z * sin(pitch),
			triangle.point_1.y * sin(pitch) + triangle.point_1.z * cos(pitch)
		);

		triangle.point_2 = Point(
			triangle.point_2.x,
			triangle.point_2.y * cos(pitch) - triangle.point_2.z * sin(pitch),
			triangle.point_2.y * sin(pitch) + triangle.point_2.z * cos(pitch)
		);

		triangle.point_3 = Point(
			triangle.point_3.x,
			triangle.point_3.y * cos(pitch) - triangle.point_3.z * sin(pitch),
			triangle.point_3.y * sin(pitch) + triangle.point_3.z * cos(pitch)
		);

		// Apply yaw
		triangle.point_1 = Point(
			triangle.point_1.x * cos(yaw) + triangle.point_1.z * sin(yaw),
			triangle.point_1.y,
			-triangle.point_1.x * sin(yaw) + triangle.point_1.z * cos(yaw)
		);

		triangle.point_2 = Point(
			triangle.point_2.x * cos(yaw) + triangle.point_2.z * sin(yaw),
			triangle.point_2.y,
			-triangle.point_2.x * sin(yaw) + triangle.point_2.z * cos(yaw)
		);

		triangle.point_3 = Point(
			triangle.point_3.x * cos(yaw) + triangle.point_3.z * sin(yaw),
			triangle.point_3.y,
			-triangle.point_3.x * sin(yaw) + triangle.point_3.z * cos(yaw)
		);

		// Apply roll
		triangle.point_1 = Point(
			triangle.point_1.x * cos(roll) - triangle.point_1.y * sin(roll),
			triangle.point_1.x * sin(roll) + triangle.point_1.y * cos(roll),
			triangle.point_1.z
		);

		triangle.point_2 = Point(
			triangle.point_2.x * cos(roll) - triangle.point_2.y * sin(roll),
			triangle.point_2.x * sin(roll) + triangle.point_2.y * cos(roll),
			triangle.point_2.z
		);

		triangle.point_3 = Point(
			triangle.point_3.x * cos(roll) - triangle.point_3.y * sin(roll),
			triangle.point_3.x * sin(roll) + triangle.point_3.y * cos(roll),
			triangle.point_3.z
		);
	}

	// Apply position
	for (auto& triangle : triangles)
	{
		triangle.point_1 += position;
		triangle.point_2 += position;
		triangle.point_3 += position;
	}
}

Hit Cube::intersect(const Ray& ray)
{
	// Check for intersection with each triangle
	Hit hit = Hit::NO_HIT();
	hit.distance = INFINITY;

	for (auto& triangle : triangles)
	{
		Hit h = triangle.intersect(ray);

		if (!h.no_hit && h.distance < hit.distance)
			hit = h;
	}

	return hit;
}
