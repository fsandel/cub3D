#include <cub3D.h>

void	set_floor_color(t_map *map, int color)
{
	map->floor_color = color;
}

void	set_ceiling_color(t_map *map, int color)
{
	map->ceiling_color = color;
}

void	set_cube_value(t_map *map, int line, int column, char c)
{
	if (c == '0')
		map->cubes[line][column] = walkable;
	else if (c == '1')
		map->cubes[line][column] = wall;
	else if (!map->has_spawn && (c == 'N' || c == 'E' || c == 'S' || c == 'W'))
	{
		set_vec(map->start_pos, column + 0.5f, line + 0.5f, 0);
		map->has_spawn = true;
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
