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

void	parse_textures(t_list *textures, t_map *map)
{
	(void) map;
	while (textures->next != NULL)
	{
		ft_printf("FloorCeiling parser: %s\n", textures->content);
		textures = textures->next;
	}
	ft_printf("FloorCeiling parser: %s\n", textures->content);
}

void	set_floor_color(t_map *map, int color)
{
	map->floor_color = color;
}

void	set_ceiling_color(t_map *map, int color)
{
	map->ceiling_color = color;
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
	i = 0;
	while (str_vals[i])
	{
		free(str_vals[i]);
		i++;
	}
	free(str_vals);
	free(temp);
}

void	parse_f_c(t_list *f_c_colors, t_map *map)
{
	char	*str;
	int		r;
	int		g;
	int		b;
	int		a;

	a = 255;
	while (f_c_colors->next != NULL)
	{
		str = (char *) f_c_colors->content;
		parse_rgb(str, &r, &g, &b);
		if (str[0] == 'F' && str[1] == ' ')
			set_floor_color(map, get_rgba(r, g, b, a));
		else if (str[0] == 'C' && str[1] == ' ')
			set_ceiling_color(map, get_rgba(r, g, b, a));
		f_c_colors = f_c_colors->next;
	}
	str = (char *) f_c_colors->content;
	parse_rgb(str, &r, &g, &b);
	if (str[0] == 'F' && str[1] == ' ')
		set_floor_color(map, get_rgba(r, g, b, a));
	else if (str[0] == 'C' && str[1] == ' ')
		set_ceiling_color(map, get_rgba(r, g, b, a));
}

void	print_file(t_list *line_list)
{
	t_list	*temp;

	temp = line_list;
	while (temp->next != NULL)
	{
		ft_printf("%s", temp->content);
		temp = temp->next;
	}
	ft_printf("%s\n", temp->content);
}
