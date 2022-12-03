#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "utils/Triple.hpp"

class Light
{
public:

	Point position;
	Color color;

	Light(const Point& position, const Color& color): position(position), color(color) {}
};

#endif
