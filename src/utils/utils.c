#include <cub3D.h>

double	min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

bool	is_on_screen(int x, int y)
{
	if (x < 0 || x > WIDTH)
		return (false);
	if (y < 0 || y > WIDTH)
		return (false);
	return (true);
}

bool	is_on_map(double x, double y, t_map *map)
{
	if (x >= 0 && y >= 0 && x < map->width && y < map->height)
		return (true);
	else
		return (false);
}
