#include <cub3D.h>

static t_cube_type	set_enemy(t_map *map, int column, int line);

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
		map->cubes[line][column] = set_enemy(map, column, line);
	else if (c == 'a')
		map->cubes[line][column] = ammo_full;
	else if (c == 'h')
		map->cubes[line][column] = ammo_empty;
	else if (c == 'x')
		map->cubes[line][column] = exit_cube;
	else
		map->cubes[line][column] = empty;
}

static t_cube_type	set_enemy(t_map *map, int column, int line)
{
	t_vector	*enemy_pos;

	enemy_pos = malloc(sizeof(t_vector));
	enemy_pos->x = column + 0.5f;
	enemy_pos->y = line + 0.5f;
	ft_lstadd_back(&map->enemy_list, ft_lstnew(enemy_pos));
	return (walkable);
}
