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

	// Move the triangles to the center
	for (auto& triangle : triangles)
	{
		triangle.point_1 -= 0.5f;
		triangle.point_2 -= 0.5f;
		triangle.point_3 -= 0.5f;
	}

	init(position, size, pitch, yaw, roll);

	texture = nullptr;
	normals = nullptr;
	specular = nullptr;
}
