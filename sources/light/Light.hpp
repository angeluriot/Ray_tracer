#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "utils/Triple.hpp"

class Light
{
public:

	Light(Point pos, Color c) : position(pos), color(c) {}

	Point position;
	Color color;
};

#endif
