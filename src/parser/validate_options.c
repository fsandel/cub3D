#include <cub3D.h>

bool	options_are_valid(t_map *map)
{
	if (!map->floor_color.bytes || !map->ceiling_color.bytes
		|| map->floor_color.bytes == 0x0
		|| map->ceiling_color.bytes == 0x0)
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
	if (map->state->contains_door && !map->door_tex)
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
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
