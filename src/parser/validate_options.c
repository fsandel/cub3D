#include <cub3D.h>

bool	options_are_valid(t_map *map)
{
	if (!map->floor_color || !map->ceiling_color || map->floor_color == -1
		|| map->ceiling_color == -1)
	{
		map->state->error_type = missing_option;
		return (false);
	}
	if (!map->textures[0] || !map->textures[1]
		|| !map->textures[2] || !map->textures[3])
	{
		map->state->error_type = missing_option;
		return (false);
	}
	if (map->state->contains_door && !map->door)
	{
		map->state->error_type = missing_option;
		return (false);
	}
	return (true);
}
