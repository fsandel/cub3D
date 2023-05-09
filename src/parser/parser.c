#include "cub3D.h"

static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content);
static void				populate_map(t_list *line_list, t_map *map);
static t_cube_type		**create_map(t_list *line_list, t_map *map);

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
	map->cubes = create_map(file_content->map_lines, map);
	if (map->state->error_type > 0)
		return (parser_error(file_content, map), NULL);
	close(fd);
	populate_map(file_content->map_lines, map);
	if (!map_is_valid(map) || map->state->error_type > 0)
		return (parser_error(file_content, map), NULL);
	parse_options(file_content->option_lines, map);
	if (!options_are_valid(map) || map->state->error_type > 0)
		return (parser_error(file_content, map), NULL);
	return (free_filecontent(file_content), map);
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

	if (!line_list)
		return (NULL);
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
		if ((is_valid_tex_str(str) || is_valid_f_c_str(str))
			&& !map->state->map_parsed)
			ft_lstadd_back(&file_content->option_lines, ft_lstnew(str));
		else if (is_valid_map_str(str))
			parse_map(&str, fd, map, file_content);
		else
		{
			if (!ft_iswhitespace(str))
			{
				free(str);
				map->state->error_type = opt_unknown;
			}
			else
				free(str);
		}
		str = get_next_line(fd);
	}
	if (!file_content->map_lines)
		map->state->error_type = invalid_map;
	return (file_content);
}
