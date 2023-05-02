#include "cub3D.h"

struct s_parser_state
{
	bool	map_parsed;
	bool	error;
};

static t_map			*init_map(void);
static t_file_content	*read_file(int fd, t_map *map, struct s_parser_state *s,
							t_file_content *file_content);
static void				populate_map(t_list *line_list, t_map *map);
static t_cube_type		**create_map(t_list *line_list, t_map *map);

void	parser_error(char *err, t_file_content *file_content, t_map *map,
			struct s_parser_state *s)
{
	(void) s;
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	if (file_content)
		free_filecontent(file_content);
	//if (s->map_parsed && map->cubes && *(map)->cubes)
	//	free_cubes(map);
	if (map)
	{
		if (map->start_dir)
			free(map->start_dir);
		if (map->start_pos)
			free(map->start_pos);
		free(map);
	}
}

// TODO: needs proper freeing on errors
t_map	*parse(int fd)
{
	t_map					*map;
	t_file_content			*file_content;
	struct s_parser_state	state;

	state.map_parsed = false;
	state.error = false;
	map = init_map();
	file_content = malloc(sizeof(t_file_content));
	if (!file_content)
		return (NULL);
	file_content->option_lines = NULL;
	file_content->map_lines = NULL;
	file_content = read_file(fd, map, &state, file_content);
	if (state.error || !file_content
		|| !file_content->map_lines || !file_content->option_lines)
		return (parser_error("Read error", file_content, map, &state), NULL);
	close(fd);
	map->cubes = create_map(file_content->map_lines, map);
	if (!map->cubes)
		return (parser_error("Invalid map", file_content, map, &state), NULL);
	populate_map(file_content->map_lines, map);
	if (!map_is_valid(map))
		return (parser_error("Invalid map", file_content, map, &state), NULL);
	parse_options(file_content->option_lines, map);
	if (!options_are_valid(map))
		return (parser_error("Invalid opts", file_content, map, &state), NULL);
	return (free_filecontent(file_content), map);
}

/*
 * inits the map struct
 */
static t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->start_pos = malloc(sizeof(t_vector));
	map->start_dir = malloc(sizeof(t_vector));
	map->width = 0;
	map->height = 0;
	map->door = NULL;
	map->has_spawn = false;
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
static t_file_content	*read_file(int fd, t_map *map, struct s_parser_state *s,
							t_file_content *file_content)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if ((is_valid_tex_str(str) || is_valid_f_c_str(str)) && !s->map_parsed)
			ft_lstadd_back(&file_content->option_lines, ft_lstnew(str));
		else if (is_valid_map_str(str))
		{
			if (s->map_parsed == false)
			{
				while (str != NULL && is_valid_map_str(str))
				{
					ft_lstadd_back(&file_content->map_lines, ft_lstnew(str));
					map->height++;
					if ((int) ft_strlen(str) - 1 > map->width)
						map->width = ft_strlen(str) - 1;
					str = get_next_line(fd);
				}
				s->map_parsed = true;
			}
			else
			{
				s->error = true;
				ft_putendl_fd("Error\nFile contains multiple maps", STDERR_FILENO);
				break ;
			}
		}
		else
		{
			if (!ft_iswhitespace(str))
			{
				s->error = true;
				free(str);
				ft_putstr_fd("Error\nUnknown option: ", STDERR_FILENO);
				ft_putendl_fd(str, STDERR_FILENO);
				break ;
			}
			else
				free(str);
		}
		str = get_next_line(fd);
	}
	return (file_content);
}
