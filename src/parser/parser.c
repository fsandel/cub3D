#include "cub3D.h"

static t_map			*init_map(void);
static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content);
static void				populate_map(t_list *line_list, t_map *map);
static t_cube_type		**create_map(t_list *line_list, t_map *map);

// TODO: needs proper freeing on errors
t_map	*parse(int fd)
{
	t_map			*map;
	t_file_content	*file_content;

	map = init_map();
	file_content = malloc(sizeof(t_file_content));
	if (!file_content)
		return (NULL);
	file_content->f_c_lines = NULL;
	file_content->texture_lines = NULL;
	file_content->map_lines = NULL;
	file_content = read_file(fd, map, file_content);
	if (!file_content)
		return (NULL);
	close(fd);
	map->cubes = create_map(file_content->map_lines, map);
	populate_map(file_content->map_lines, map);
	parse_textures(file_content->texture_lines, map);
	parse_f_c(file_content->f_c_lines, map);
	ft_lstclear(&file_content->map_lines, &free);
	ft_lstclear(&file_content->texture_lines, &free);
	ft_lstclear(&file_content->f_c_lines, &free);
	free(file_content);
	return (map);
}

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
	return (map);
}

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
		while ((line_s[col] != '\0' || col < map->width) && line_s[0] != '\n')
		{
			set_cube_value(map, line, col, line_s[col]);
			col++;
		}
		line++;
		line_list = line_list->next;
	}
}

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

static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content)
{
	char	*str;

	str = get_next_line(fd);
	while (str != NULL)
	{
		if (is_valid_tex_str(str))
			ft_lstadd_back(&file_content->texture_lines, ft_lstnew(str));
		else if (is_valid_f_c_str(str))
			ft_lstadd_back(&file_content->f_c_lines, ft_lstnew(str));
		else if (is_valid_map_str(str))
		{
			ft_lstadd_back(&file_content->map_lines, ft_lstnew(str));
			map->height++;
			if ((int) ft_strlen(str) - 1 > map->width)
				map->width = ft_strlen(str) - 1;
		}
		else
			free(str);
		str = get_next_line(fd);
	}
	return (file_content);
}
