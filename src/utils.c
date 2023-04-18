#include <cub3D.h>

int	on_screen(int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (1);
	else
		return (0);
}

t_cube_type	get_cube_type(t_vector *pos, t_map *map)
{
	int	width;
	int	height;

	if (pos->x > map->width || pos->x < 0)
		return (wall);
	if (pos->y > map->height || pos->y < 0)
		return (wall);
	return (map->cubes[(int)pos->y][(int)pos->x]);
}
