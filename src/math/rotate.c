#include <cub3D.h>

void	norm(t_vector *v, double future_length)
{
	double	length;

	length = sqrt((v->x * v->x) + (v->y * v->y));
	v->x = v->x / length * future_length;
	v->y = v->y / length * future_length;
}

void	rotate(t_vector *before, t_vector *after, double angle)
{
	const double	x = before->x;
	const double	y = before->y;

	after->x = x * cos(angle) - y * sin(angle);
	after->y = x * sin(angle) + y * cos(angle);
	norm(after, 1);
}
