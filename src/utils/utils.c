#include <cub3D.h>

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

bool	is_on_map(double x, double y, t_map *map)
{
	if (x >= 0 && y >= 0 && x < map->width && y < map->height)
		return (true);
	else
		return (false);
}
