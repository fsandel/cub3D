#include <cub3D.h>

double	quad_add(double x, double y)
{
	return (sqrt(x * x + y * y));
}

double	ft_modf(double num)
{
	return (num - (int)num);
}

int	sign(double x)
{
	return ((x > 0) - (x < 0));
}
