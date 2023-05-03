#include <cub3D.h>

double	distance(t_vector pos, t_vector target)
{
	double	dis;
	double	x;
	double	y;

	x = pow(pos.x - target.x, 2);
	y = pow(pos.y - target.y, 2);
	dis = sqrt(x + y);
	return (dis);
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double	abs_vector(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

double	distance_perpendicular(t_vector pos, t_vector dir, t_vector target)
{
	t_vector	norm;
	t_vector	pos2;
	double		upper;
	double		lower;

	rotate(&dir, &norm, M_PI_2);
	pos2 = (t_vector){pos.x + norm.x, pos.y + norm.y};
	upper = fabs((pos2.x - pos.x) * (pos.y - target.y)
			- (pos.x - target.x) * (pos2.y - pos.y));
	lower = sqrt(pow(pos2.x - pos.x, 2) + pow(pos2.y - pos.y, 2));
	return (upper / lower);
}
