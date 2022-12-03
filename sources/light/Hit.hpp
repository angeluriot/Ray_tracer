#ifndef HIT_HPP
#define HIT_HPP

#include <limits>
#include "utils/Triple.hpp"

class Hit
{
public:

	double distance;
	Vector normal;
	bool no_hit;

	Hit(const double distance, const Vector& normal, bool no_hit = false): distance(distance), normal(normal), no_hit(no_hit) {}

	static const Hit NO_HIT()
	{
		static Hit no_hit(std::numeric_limits<double>::quiet_NaN(), Vector(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()), true);
		return no_hit;
	}
};

#endif
