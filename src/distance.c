#include <cub3D.h>

double	distance(t_vector_f pos, t_vector_f target)
{
	double	dis;
	double	x;
	double	y;
	double	z;

	x = pow(pos.x - target.x, 2);
	y = pow(pos.y - target.y, 2);
	z = pow(pos.z - target.z, 2);
	dis = sqrt(x + y + z);
	return (dis);
}

double dotProduct(t_vector_f v1, t_vector_f v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double abs_vector(t_vector_f v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

// double distancePerp(t_vector_f pos, t_vector_f dir, t_vector_f target)
// {
// 	double		projection;
// 	t_vector_f	v;
// 	t_vector_f	projectedPoint;
// 	t_vector_f	distanceVector;

// 	v = (t_vector_f){target.x - pos.x, target.y - pos.y, target.z - pos.z};
// 	projection = dotProduct(v, dir) / abs_vector(dir);
// 	projectedPoint.x = pos.x + projection * dir.x;
// 	projectedPoint.y = pos.y + projection * dir.y;
// 	projectedPoint.z = pos.z + projection * dir.z;
// 	distanceVector.x = target.x - projectedPoint.x;
// 	distanceVector.y = target.y - projectedPoint.y;
// 	distanceVector.z = target.z - projectedPoint.z;
// 	return (abs_vector(distanceVector));
// }


double distancePerp(t_vector_f pos, t_vector_f dir, t_vector_f target)
{
	t_vector_f	norm;
	t_vector_f	pos2;
	double		upper;
	double		lower;

	rotate_hor_f(&dir, &norm, M_PI_2);
	pos2 = (t_vector_f){pos.x + norm.x, pos.y + norm.y, pos.z + norm.z};

	upper = fabs((pos2.x - pos.x)*(pos.y - target.y) - (pos.x - target.x)*(pos2.y-pos.y));
	lower = sqrt(pow(pos2.x - pos.x, 2) + pow(pos2.y - pos.y, 2));
	return (upper / lower);
}
