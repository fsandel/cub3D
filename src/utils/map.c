#include <cub3D.h>

void	set_floor_color(t_map *map, int color)
{
	if (!map->state->f_parsed)
	{
		map->floor_color = color;
		map->state->f_parsed = true;
	}
	else
		map->state->error_type = too_many_colors;
}

void	set_ceiling_color(t_map *map, int color)
{
	if (!map->state->c_parsed)
	{
		map->ceiling_color = color;
		map->state->c_parsed = true;
	}
	else
		map->state->error_type = too_many_colors;
}

void	set_cube_value(t_map *map, int line, int column, char c)
{
	if (c == '0')
		map->cubes[line][column] = walkable;
	else if (c == '1')
		map->cubes[line][column] = wall;
	else if (!map->has_spawn && (c == 'N' || c == 'E' || c == 'S' || c == 'W'))
	{
		if (!map->has_spawn)
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
			map->state->error_type = too_many_spawns;
	}
	else if (c == 'D')
		map->cubes[line][column] = door_closed;
	else
		map->cubes[line][column] = empty;
}
