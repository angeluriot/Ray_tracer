#ifndef HIT_HPP
#define HIT_HPP

#include <limits>
#include "utils/Triple.hpp"

class Hit
{
public:

	float distance;
	Vector normal;
	Color color;
	bool no_hit;

	Hit(float distance, const Vector& normal, const Color& color, bool no_hit = false): distance(distance), normal(normal), color(color), no_hit(no_hit) {}

	static const Hit NO_HIT()
	{
		static Hit no_hit(std::numeric_limits<float>::quiet_NaN(), Vector(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()), Color(0.f, 0.f, 0.f), true);
		return no_hit;
	}
};

#endif
