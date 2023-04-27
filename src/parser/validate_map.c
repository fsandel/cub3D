#include <cub3D.h>

bool	is_valid_field(t_map *map, int line, int column);

bool	map_is_valid(t_map *map)
{
	int	line;
	int	column;

	line = 0;
	if (map->width < 3 || map->height < 3)
		return (false);
	if (!map->has_spawn)
		return (false);
	while (line < map->height)
	{
		column = 0;
		while (column < map->width)
		{
			if (map->cubes[line][column] == walkable
				&& !is_valid_field(map, line, column))
				return (false);
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