#include <cub3D.h>

void	set_map_value(t_map *map, int line, int column, char c)
{
	if (c == '0')
		map->cubes[line][column] = walkable;
	else if (c == '1')
		map->cubes[line][column] = wall;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		map->start_pos->x = (column * WIDTH) / map->width;
		map->start_pos->y = (line * HEIGHT) / map->height;
		map->start_pos->z = 0;
		if (c == 'N')
			set_vec(map->start_dir, 0, 1, 0);
		else if (c == 'E')
			set_vec(map->start_dir, -1, 0, 0);
		else if (c == 'S')
			set_vec(map->start_dir, 0, -1, 0);
		else if (c == 'W')
			set_vec(map->start_dir, 1, 0, 0);
		map->cubes[line][column] = walkable;
	}
	else
		map->cubes[line][column] = empty;
}
