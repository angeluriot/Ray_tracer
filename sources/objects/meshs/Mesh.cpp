#include "objects/meshs/Mesh.hpp"
#include "objects/Triangle.hpp"
#include "glm/glm.h"
#include "objects/meshs/Cube.hpp"

Mesh::Mesh(const std::string& filename, const Point& position, float size, float pitch, float yaw, float roll)
{
	std::string path = filename;

	// Load the model
	GLMmodel* model = glmReadOBJ(path.data());

	// Scale the model
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90.0f);

	// Create the triangles
	for (unsigned int i = 0; i < model->numtriangles; i++)
	{
		GLMtriangle triangle = model->triangles[i];

		Point p1 = Point(model->vertices[3 * triangle.vindices[0] + 0], model->vertices[3 * triangle.vindices[0] + 1], model->vertices[3 * triangle.vindices[0] + 2]);
		Point p2 = Point(model->vertices[3 * triangle.vindices[1] + 0], model->vertices[3 * triangle.vindices[1] + 1], model->vertices[3 * triangle.vindices[1] + 2]);
		Point p3 = Point(model->vertices[3 * triangle.vindices[2] + 0], model->vertices[3 * triangle.vindices[2] + 1], model->vertices[3 * triangle.vindices[2] + 2]);

		triangles.push_back(Triangle(p1, p2, p3));
	}

	// Free the model
	glmDelete(model);

	init(position, size, pitch, yaw, roll);

	Point box_corner_1 = Point(triangles[0].point_1.x, triangles[0].point_1.y, triangles[0].point_1.z);
	Point box_corner_2 = Point(triangles[0].point_1.x, triangles[0].point_1.y, triangles[0].point_1.z);;

	for (auto& triangle : triangles)
	{
		if (box_corner_1.x < triangle.point_1.x)
			box_corner_1.x = triangle.point_1.x;
		if (box_corner_1.y < triangle.point_1.y)
			box_corner_1.y = triangle.point_1.y;
		if (box_corner_1.z < triangle.point_1.z)
			box_corner_1.z = triangle.point_1.z;
		if (box_corner_1.x < triangle.point_2.x)
			box_corner_1.x = triangle.point_2.x;
		if (box_corner_1.y < triangle.point_2.y)
			box_corner_1.y = triangle.point_2.y;
		if (box_corner_1.z < triangle.point_2.z)
			box_corner_1.z = triangle.point_2.z;
		if (box_corner_1.x < triangle.point_3.x)
			box_corner_1.x = triangle.point_3.x;
		if (box_corner_1.y < triangle.point_3.y)
			box_corner_1.y = triangle.point_3.y;
		if (box_corner_1.z < triangle.point_3.z)
			box_corner_1.z = triangle.point_3.z;

		if (box_corner_2.x > triangle.point_1.x)
			box_corner_2.x = triangle.point_1.x;
		if (box_corner_2.y > triangle.point_1.y)
			box_corner_2.y = triangle.point_1.y;
		if (box_corner_2.z > triangle.point_1.z)
			box_corner_2.z = triangle.point_1.z;
		if (box_corner_2.x > triangle.point_2.x)
			box_corner_2.x = triangle.point_2.x;
		if (box_corner_2.y > triangle.point_2.y)
			box_corner_2.y = triangle.point_2.y;
		if (box_corner_2.z > triangle.point_2.z)
			box_corner_2.z = triangle.point_2.z;
		if (box_corner_2.x > triangle.point_3.x)
			box_corner_2.x = triangle.point_3.x;
		if (box_corner_2.y > triangle.point_3.y)
			box_corner_2.y = triangle.point_3.y;
		if (box_corner_2.z > triangle.point_3.z)
			box_corner_2.z = triangle.point_3.z;
	}

	box = new Cube(Point((box_corner_1.x + box_corner_2.x) / 2, (box_corner_1.y + box_corner_2.y) / 2, (box_corner_1.z + box_corner_2.z) / 2),
			   (float)sqrt(pow(box_corner_1.x - box_corner_2.x, 2) + pow(box_corner_1.y - box_corner_2.y, 2) + pow(box_corner_1.z - box_corner_2.z, 2)), 0.f, 0.f, 0.f);

	texture = nullptr;
	normals = nullptr;
	specular = nullptr;
}

void Mesh::init(const Point& position, float size, float pitch, float yaw, float roll)
{
	// Apply scale
	for (auto& triangle : triangles)
	{
		triangle.point_1 *= size;
		triangle.point_2 *= size;
		triangle.point_3 *= size;
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

Hit Mesh::intersect(const Ray& ray) const
{
	// Check for intersection with each triangle
	Hit min_hit(std::numeric_limits<float>::infinity(), Vector(), Color(), 1.f, true);

	if (box != nullptr && box->intersect(ray).no_hit)
		return Hit::NO_HIT();

	for (auto& triangle : triangles)
	{
		Hit hit = triangle.intersect(ray);

		if (!hit.no_hit && hit.distance < min_hit.distance)
			min_hit = hit;
	}

	min_hit.color = material.color;

	return min_hit;
}
