#include <cub3D.h>

void	parse_texture(char *input, t_map *map)
{
	char			**str_vals;
	char			*temp;
	mlx_texture_t	*texture;

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
	ft_arr_free(str_vals);
	free(temp);
}

void	parse_textures(t_list *textures, t_map *map)
{
	while (textures != NULL)
	{
		parse_texture(textures->content, map);
		textures = textures->next;
	}
}

void	parse_f_c(t_list *f_c_colors, t_map *map)
{
	char	*str;
	int		r;
	int		g;
	int		b;
	int		a;

	a = 255;
	while (f_c_colors != NULL)
	{
		str = (char *) f_c_colors->content;
		parse_rgb(str, &r, &g, &b);
		if (str[0] == 'F' && str[1] == ' ')
			set_floor_color(map, get_rgba(r, g, b, a));
		else if (str[0] == 'C' && str[1] == ' ')
			set_ceiling_color(map, get_rgba(r, g, b, a));
		f_c_colors = f_c_colors->next;
	}
}
