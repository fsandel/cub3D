#include <cub3D.h>

double	border(double lower_bound, double value, double upper_bound)
{
	if (value > upper_bound)
		return (upper_bound);
	if (value < lower_bound)
		return (lower_bound);
	return (value);
}
