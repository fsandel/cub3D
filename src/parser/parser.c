#include "cub3D.h"

// Read-Errors
#define OPT_UNKNWON "Found unexpected option"
#define NO_MAP "File doesn't contain valid map"
#define NO_OPTS "File has no options"
#define MAP_NOT_LAST "No options specified before map"
#define MULTIPLE_MAPS "File contains multiple maps"
// Parse-Errors
#define INVALID_TEXTURE "File contains invalid texture"
#define INVALID_COLOR "Options contain invalid color"
#define TOO_MANY_TEXTURES "File contains too many textures"
#define TOO_MANY_SPAWNS "File contains too many spawn positions"
#define TOO_MANY_COLORS "File contains too many color options"
// Validation-Errors
#define MISSING_OPTION "File misses a mandatory option"
#define INVALID_MAP "Map is invalid - not playable"

static t_map			*init_map(void);
static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content);
static void				populate_map(t_list *line_list, t_map *map);
static t_cube_type		**create_map(t_list *line_list, t_map *map);

void	print_error(enum e_parser_error err)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (err == opt_unknown)
		ft_putendl_fd(OPT_UNKNWON, STDERR_FILENO);
	else if (err == no_map)
		ft_putendl_fd(NO_MAP, STDERR_FILENO);
	else if (err == multiple_maps)
		ft_putendl_fd(MULTIPLE_MAPS, STDERR_FILENO);
	else if (err == map_not_last)
		ft_putendl_fd(MAP_NOT_LAST, STDERR_FILENO);
	else if (err == no_opts)
		ft_putendl_fd(NO_OPTS, STDERR_FILENO);
	else if (err == invalid_texture)
		ft_putendl_fd(INVALID_TEXTURE, STDERR_FILENO);
	else if (err == invalid_color)
		ft_putendl_fd(INVALID_COLOR, STDERR_FILENO);
	else if (err == too_many_textures)
		ft_putendl_fd(TOO_MANY_TEXTURES, STDERR_FILENO);
	else if (err == too_many_spawns)
		ft_putendl_fd(TOO_MANY_SPAWNS, STDERR_FILENO);
	else if (err == too_many_colors)
		ft_putendl_fd(TOO_MANY_COLORS, STDERR_FILENO);
	else if (err == missing_option)
		ft_putendl_fd(MISSING_OPTION, STDERR_FILENO);
	else if (err == invalid_map)
		ft_putendl_fd(INVALID_MAP, STDERR_FILENO);
}

void	parser_error(t_file_content *file_content, t_map *map)
{
	print_error(map->state->error_type);
	if (file_content)
		free_filecontent(file_content);
	if (map->state->map_parsed && map->cubes && *(map)->cubes)
		free_cubes(map);
	if (map)
	{
		if (map->start_dir)
			free(map->start_dir);
		if (map->start_pos)
			free(map->start_pos);
		free(map->state);
		free(map);
	}
}

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
