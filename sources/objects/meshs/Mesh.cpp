#include "objects/meshs/Mesh.hpp"

Mesh::~Mesh() {}

Hit Mesh::intersect(const Ray& ray) const
{
	// Check for intersection with each triangle
	Hit min_hit(std::numeric_limits<float>::infinity(), Vector(), Color());

	for (auto& triangle : triangles)
	{
		Hit hit = triangle.intersect(ray);

		if (!hit.no_hit && hit.distance < min_hit.distance)
			min_hit = hit;
	}

	return min_hit;
}
