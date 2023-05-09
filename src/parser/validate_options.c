#include <cub3D.h>

bool	options_are_valid(t_map *map)
{
	if (!map->floor_color || !map->ceiling_color
		|| map->floor_color == get_rgba(0, 0, 0, 0)
		|| map->ceiling_color == get_rgba(0, 0, 0, 0))
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

bool	is_num_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
