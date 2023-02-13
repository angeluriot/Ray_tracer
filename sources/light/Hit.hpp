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
	float specular;
	bool no_hit;

	Hit(float distance, const Vector& normal, const Color& color, float specular = 1.f, bool no_hit = false): distance(distance), normal(normal), color(color), specular(specular), no_hit(no_hit) {}

	static const Hit NO_HIT()
	{
		static Hit no_hit(std::numeric_limits<float>::quiet_NaN(), Vector(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()), Color(0.f, 0.f, 0.f), 1.f, true);
		return no_hit;
	}
};

#endif
