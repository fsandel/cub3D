#include <cub3D.h>

void	parse_texture(char *input, t_map *map)
{
	char			**str_vals;
	char			*temp;
	mlx_texture_t	*texture;
	int				i;

	str_vals = ft_split(input, ' ');
	temp = ft_strtrim(str_vals[1], "\n");
	texture = mlx_load_png(temp);
	if (ft_strncmp(str_vals[0], "NO", 2) == 0)
		map->textures[north] = texture;
	else if (ft_strncmp(str_vals[0], "SO", 2) == 0)
		map->textures[south] = texture;
	else if (ft_strncmp(str_vals[0], "WE", 2) == 0)
		map->textures[west] = texture;
	else if (ft_strncmp(str_vals[0], "EA", 2) == 0)
		map->textures[east] = texture;
	i = 0;
	while (str_vals[i])
	{
		free(str_vals[i]);
		i++;
	}
	free(str_vals);
	free(temp);
}

void	parse_textures(t_list *textures, t_map *map)
{
	(void) map;
	while (textures->next != NULL)
	{
		parse_texture(textures->content, map);
		textures = textures->next;
	}
	parse_texture(textures->content, map);
}

void	set_floor_color(t_map *map, int color)
{
	map->floor_color = color;
}

void	set_ceiling_color(t_map *map, int color)
{
	map->ceiling_color = color;
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
