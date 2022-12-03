#include "utils/Triple.hpp"

std::ostream& operator<<(std::ostream& stream, const Triple& triple)
{
	return stream << '[' << triple.x << ', ' << triple.y << ', ' << triple.z << ']';
}
