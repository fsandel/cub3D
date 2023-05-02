#include <cub3D.h>

static int	parse_rgb(char *str, int *r, int *g, int *b);
static void	parse_f_c(char *f_c_colors, t_map *map);
static void	parse_texture(char *input, t_map *map);

void	parse_options(t_list *option_lines, t_map *map)
{
	while (option_lines != NULL)
	{
		if (is_valid_f_c_str(option_lines->content))
			parse_f_c(option_lines->content, map);
		else if (is_valid_tex_str(option_lines->content))
			parse_texture(option_lines->content, map);
		option_lines = option_lines->next;
	}
}

static void	parse_texture(char *input, t_map *map)
{
	char			**str_vals;
	char			*temp;
	mlx_texture_t	*texture;

	str_vals = ft_split(input, ' ');
	temp = ft_strtrim(str_vals[1], "\n");
	texture = mlx_load_png(temp);
	if (!texture)
		map->state->error_type = invalid_texture;
	if (ft_strncmp(str_vals[0], "NO", 2) == 0)
		map->textures[north] = texture;
	else if (ft_strncmp(str_vals[0], "SO", 2) == 0)
		map->textures[south] = texture;
	else if (ft_strncmp(str_vals[0], "WE", 2) == 0)
		map->textures[west] = texture;
	else if (ft_strncmp(str_vals[0], "EA", 2) == 0)
		map->textures[east] = texture;
	else if (ft_strncmp(str_vals[0], "DO", 2) == 0)
		map->door = texture;
	ft_arr_free(str_vals);
	free(temp);
}

static void	parse_f_c(char *f_c_colors, t_map *map)
{
	int	r;
	int	g;
	int	b;
	int	a;
	int	success;

	a = 255;
	success = parse_rgb(f_c_colors, &r, &g, &b);
	if (success == 1)
		map->state->error_type = invalid_color;
	if (f_c_colors[0] == 'F' && f_c_colors[1] == ' ')
		set_floor_color(map, get_rgba(r, g, b, a));
	else if (f_c_colors[0] == 'C' && f_c_colors[1] == ' ')
		set_ceiling_color(map, get_rgba(r, g, b, a));
}

// TODO needs to throw an error if one of the values is  < 0 or > 255
static int	parse_rgb(char *str, int *r, int *g, int *b)
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
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
