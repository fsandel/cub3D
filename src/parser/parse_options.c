#include <cub3D.h>

static int	parse_rgb(char *str, int *r, int *g, int *b);
static void	parse_f_c(char *f_c_colors, t_map *map);
static void	parse_texture(char *input, t_map *map);

void	parse_map(char **str, int fd, t_map *map, t_file_content *file_content)
{
	if (map->state->map_parsed == false)
	{
		while (*str != NULL && is_valid_map_str(*str))
		{
			ft_lstadd_back(&file_content->map_lines, ft_lstnew(*str));
			map->height++;
			if ((int) ft_strlen(*str) - 1 > map->width)
				map->width = ft_strlen(*str) - 1;
			*str = get_next_line(fd);
		}
		map->state->map_parsed = true;
	}
	else
		map->state->error_type = multiple_maps;
}

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
	if (ft_strncmp(str_vals[0], "NO", 2) == 0 && !map->textures[north])
		map->textures[north] = texture;
	else if (ft_strncmp(str_vals[0], "SO", 2) == 0 && !map->textures[south])
		map->textures[south] = texture;
	else if (ft_strncmp(str_vals[0], "WE", 2) == 0 && !map->textures[west])
		map->textures[west] = texture;
	else if (ft_strncmp(str_vals[0], "EA", 2) == 0 && !map->textures[east])
		map->textures[east] = texture;
	else if (ft_strncmp(str_vals[0], "DO", 2) == 0 && !map->door)
		map->door = texture;
	else
		map->state->error_type = too_many_textures;
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

static int	parse_rgb(char *str, int *r, int *g, int *b)
{
	char	*temp;
	char	**str_vals;
	int		i;

	temp = ft_strtrim(str, "FC \n");
	str_vals = ft_split(temp, ',');
	if (ft_arr_size(str_vals) != 3)
		return (ft_arr_free(str_vals), free(temp), EXIT_FAILURE);
	i = 0;
	while (i < 3)
	{
		temp = ft_strtrim(str_vals[i], " ");
		if (!is_num_str(temp))
			return (ft_arr_free(str_vals), free(temp), EXIT_FAILURE);
		if (i == 0)
			*r = ft_atoi(str_vals[i]);
		else if (i == 1)
			*g = ft_atoi(str_vals[i]);
		else if (i == 2)
			*b = ft_atoi(str_vals[i]);
		i++;
	}
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (ft_arr_free(str_vals), free(temp), EXIT_FAILURE);
	return (ft_arr_free(str_vals), free(temp), EXIT_SUCCESS);
}
