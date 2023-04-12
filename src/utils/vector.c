#include <cub3D.h>

t_vector	*set_vec(t_vector *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}
