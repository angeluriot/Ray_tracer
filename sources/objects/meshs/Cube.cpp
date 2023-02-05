#include "objects/meshs/Cube.hpp"

Cube::Cube(const Point& position, float size, float pitch, float yaw, float roll)
{
	// Create the 12 triangles of the cube
	triangles.push_back(Triangle(Point(0.f, 0.f, 0.f), Point(0.f, 0.f, 1.f), Point(0.f, 1.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 0.f, 1.f), Point(0.f, 1.f, 1.f), Point(0.f, 1.f, 0.f)));
	triangles.push_back(Triangle(Point(1.f, 0.f, 1.f), Point(1.f, 0.f, 0.f), Point(1.f, 1.f, 0.f)));
	triangles.push_back(Triangle(Point(1.f, 1.f, 1.f), Point(1.f, 0.f, 1.f), Point(1.f, 1.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 0.f, 1.f), Point(0.f, 0.f, 0.f), Point(1.f, 0.f, 0.f)));
	triangles.push_back(Triangle(Point(1.f, 0.f, 1.f), Point(0.f, 0.f, 1.f), Point(1.f, 0.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 1.f, 0.f), Point(0.f, 1.f, 1.f), Point(1.f, 1.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 1.f, 1.f), Point(1.f, 1.f, 1.f), Point(1.f, 1.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 0.f, 0.f), Point(0.f, 1.f, 0.f), Point(1.f, 0.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 1.f, 0.f), Point(1.f, 1.f, 0.f), Point(1.f, 0.f, 0.f)));
	triangles.push_back(Triangle(Point(0.f, 1.f, 1.f), Point(0.f, 0.f, 1.f), Point(1.f, 0.f, 1.f)));
	triangles.push_back(Triangle(Point(1.f, 1.f, 1.f), Point(0.f, 1.f, 1.f), Point(1.f, 0.f, 1.f)));

	// Apply scale
	for (auto& triangle : triangles)
	{
		triangle.point_1 = (triangle.point_1 - 0.5f) * size;
		triangle.point_2 = (triangle.point_2 - 0.5f) * size;
		triangle.point_3 = (triangle.point_3 - 0.5f) * size;
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

	texture = nullptr;
}
