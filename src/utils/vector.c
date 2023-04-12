#include <cub3D.h>

t_vector_f	*set_vec(t_vector_f *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}
