#include "cub3D.h"

static t_map			*init_map(void);
static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content);
static void				populate_map(t_list *line_list, t_map *map);
static t_cube_type		**create_map(t_list *line_list, t_map *map);

// TODO: needs proper freeing on errors
t_map	*parse(int fd)
{
	t_map					*map;
	t_file_content			*file_content;

	map = init_map();
	file_content = malloc(sizeof(t_file_content));
	if (!file_content)
		return (NULL);
	file_content->option_lines = NULL;
	file_content->map_lines = NULL;
	file_content = read_file(fd, map, file_content);
	if (map->state->error_type > 0)
		return (parser_error(file_content, map), NULL);
	close(fd);
	map->cubes = create_map(file_content->map_lines, map);
	populate_map(file_content->map_lines, map);
	if (!map_is_valid(map) || map->state->error_type > 0)
		return (parser_error(file_content, map), NULL);
	parse_options(file_content->option_lines, map);
	if (!options_are_valid(map) || map->state->error_type > 0)
		return (parser_error(file_content, map), NULL);
	return (free_filecontent(file_content), map);
}

/*
 * inits the map struct
 */
static t_map	*init_map(void)
{
	t_map			*map;
	t_parser_state	*state;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->start_pos = malloc(sizeof(t_vector));
	map->start_dir = malloc(sizeof(t_vector));
	map->textures[0] = NULL;
	map->textures[1] = NULL;
	map->textures[2] = NULL;
	map->textures[3] = NULL;
	map->width = 0;
	map->height = 0;
	map->door = NULL;
	map->has_spawn = false;
	state = malloc(sizeof(t_parser_state));
	if (!state)
		return (NULL);
	state->map_parsed = false;
	state->f_parsed = false;
	state->c_parsed = false;
	state->contains_door = false;
	state->error_type = no_error;
	map->state = state;
	return (map);
}

/*
 * fills a previously allocated map with corresponding cubes, specified by the
 * line_list
 */
static void	populate_map(t_list *line_list, t_map *map)
{
	int		line;
	int		col;
	char	*line_s;

	line = 0;
	while (line_list != NULL)
	{
		line_s = (char *) line_list->content;
		col = 0;
		while (col < map->width)
		{
			if ((size_t) col < ft_strlen(line_s))
				set_cube_value(map, line, col, line_s[col]);
			else
				set_cube_value(map, line, col, ' ');
			col++;
		}
		line++;
		line_list = line_list->next;
	}
}

/*
 * allocates necessary memory for the map
 */
static t_cube_type	**create_map(t_list *line_list, t_map *map)
{
	t_list		*temp;
	t_cube_type	**res;
	int			i;

	res = malloc((map->height + 1) * sizeof(t_cube_type *));
	if (!res)
		return (NULL);
	temp = line_list;
	i = 0;
	while (temp != NULL)
	{
		res[i] = malloc((map->width + 1) * sizeof(t_cube_type));
		temp = temp->next;
		i++;
	}
	return (res);
}

/*
 * reads line by line from fd, adds line to map_lines or option_lines
 * and counts the mapwidth and height
 */
static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if ((is_valid_tex_str(str) || is_valid_f_c_str(str)) && !map->state->map_parsed)
			ft_lstadd_back(&file_content->option_lines, ft_lstnew(str));
		else if (is_valid_map_str(str))
		{
			if (map->state->map_parsed == false)
			{
				while (str != NULL && is_valid_map_str(str))
				{
					ft_lstadd_back(&file_content->map_lines, ft_lstnew(str));
					map->height++;
					if ((int) ft_strlen(str) - 1 > map->width)
						map->width = ft_strlen(str) - 1;
					str = get_next_line(fd);
				}
				map->state->map_parsed = true;
			}
			else
			{
				map->state->error_type = multiple_maps;
				free(str);
				break ;
			}
		}
		else
		{
			if (!ft_iswhitespace(str))
			{
				map->state->error_type = opt_unknown;
				free(str);
				break ;
			}
			else
				free(str);
		}
		str = get_next_line(fd);
	}
	return (file_content);
}
