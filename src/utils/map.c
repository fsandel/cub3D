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
		set_vec(map->start_pos, column + 0.5f, line + 0.5f);
		map->has_spawn = true;
		if (c == 'N')
			set_vec(map->start_dir, 0, 1);
		else if (c == 'E')
			set_vec(map->start_dir, -1, 0);
		else if (c == 'S')
			set_vec(map->start_dir, 0, -1);
		else if (c == 'W')
			set_vec(map->start_dir, 1, 0);
		map->cubes[line][column] = walkable;
	}
	else if (c == 'D')
		map->cubes[line][column] = door_closed;
	else if (c == 'e')
	{
		map->cubes[line][column] = enemy;
		ft_lstadd_back(&map->enemy_list, ft_lstnew(&(t_vector){column, line}));
	}
	else
		map->cubes[line][column] = empty;
}
