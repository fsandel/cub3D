#include <cub3D.h>

bool	is_valid_field(t_map *map, int line, int column);

bool	map_is_valid(t_map *map)
{
	int	line;
	int	column;

	line = 0;
	while (line < map->height)
	{
		column = 0;
		while (column < map->width)
		{
			printf("at: %d x: %d y: %d\n", (int) map->cubes[line][column], column, line);
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
	printf("valid field? %d at x: %d y: %d\n",
		(int) map->cubes[line][column], column, line);
	if (line == 0 || line == map->height || column == 0 || column == map->width)
		return (printf("first or last line/column\n"), false);
	if (map->cubes[line][column - 1] == empty)
		return (printf("prior is illegal\n"), false);
	if (map->cubes[line][column + 1] == empty)
		return (printf("next is illegal\n"), false);
	if (map->cubes[line - 1][column] == empty)
		return (printf("upper is illegal\n"), false);
	if (map->cubes[line + 1][column] == empty)
		return (printf("lower is illegal\n"), false);
	return (true);
}
