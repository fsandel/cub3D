#include <cub3D.h>

void	set_map_value(t_map *map, int line, int column, char c)
{
	if (c == '0')
		map->cubes[line][column] = walkable;
	else if (c == '1')
		map->cubes[line][column] = wall;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		map->start_pos->x = (column * WIDTH) / map->width;
		map->start_pos->y = (line * HEIGHT) / map->height;
		map->start_pos->z = 0;
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
		map->cubes[line][column] = empty;
}

void	parse_rgb(char *str, int *r, int *g, int *b)
{
	char	*temp;
	char	**str_vals;
	int		i;

	temp = ft_strtrim(str, "FC ");
	str_vals = ft_split(temp, ',');
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			*r = ft_atoi(str_vals[i]);
		else if (i == 1)
			*g = ft_atoi(str_vals[i]);
		else if (i == 2)
			*b = ft_atoi(str_vals[i]);
		i++;
	}
	ft_arr_free(str_vals);
	free(temp);
}
