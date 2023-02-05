#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include "objects/meshs/Mesh.hpp"

class Cube : public Mesh
{
public:

	Cube() = default;
	Cube(const Point& position, float size, float pitch, float yaw, float roll);
};

#endif
