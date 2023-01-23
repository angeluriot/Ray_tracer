#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <array>
#include "utils/Triple.hpp"

class Camera
{
public:

	Point position;
	Vector direction;
	Vector up;
};

#endif
