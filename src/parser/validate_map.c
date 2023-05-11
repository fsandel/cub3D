#include <cub3D.h>

bool	is_valid_field(t_map *map, int line, int column);

bool	map_is_valid(t_map *map)
{
	int	line;
	int	column;

	line = 0;
	if (map->width < 3 || map->height < 3 || !map->has_spawn)
		return (map->state->error_type = invalid_map, false);
	while (line < map->height)
	{
		column = 0;
		while (column < map->width)
		{
			if ((map->cubes[line][column] <= walkable
				|| map->cubes[line][column] == door_closed
				|| map->cubes[line][column] == destructible)
				&& !is_valid_field(map, line, column))
			{
				map->state->error_type = invalid_map;
				return (false);
			}
			column++;
		}
		line++;
	}
	return (true);
}

bool	is_valid_field(t_map *map, int line, int column)
{
	if (line == 0 || line == map->height - 1
		|| column == 0 || column == map->width - 1)
		return (false);
	if (map->cubes[line][column - 1] == empty)
		return (false);
	if (map->cubes[line][column + 1] == empty)
		return (false);
	if (map->cubes[line - 1][column] == empty)
		return (false);
	if (map->cubes[line + 1][column] == empty)
		return (false);
	return (true);
}
