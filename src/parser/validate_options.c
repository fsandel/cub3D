#include <cub3D.h>

bool	options_are_valid(t_map *map)
{
	if (!map->floor_color || !map->ceiling_color)
		return (false);
	if (!map->textures[0] || !map->textures[1]
		|| !map->textures[2] || !map->textures[3])
		return (false);
	return (true);
}
