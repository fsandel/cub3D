#include <cub3D.h>

t_cube_type	get_cube_type(t_vector *pos, t_map *map)
{
	if (pos->x >= map->width || pos->x < 0)
		return (wall);
	if (pos->y >= map->height || pos->y < 0)
		return (wall);
	return (map->cubes[(int)pos->y][(int)pos->x]);
}
