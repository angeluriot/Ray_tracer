#include "utils/Triple.hpp"

std::ostream& operator<<(std::ostream& s, const Triple& v)
{
	return s << '[' << v.x << ',' << v.y << ',' << v.z << ']';
}
