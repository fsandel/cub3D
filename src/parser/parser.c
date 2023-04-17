#include "cub3D.h"

static t_map			*init_map(void);
static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content);
static void				populate_map(t_list *line_list, t_map *map);
static t_cube_type		**create_map(t_list *line_list, t_map *map);

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
	close(fd);
	map->cubes = NULL;
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
	return (map);
}

static void	populate_map(t_list *line_list, t_map *map)
{
	int		line;
	int		col;
	char	*line_s;

	line = 0;
	while (line_list->next != NULL)
	{
		line_s = (char *) line_list->content;
		col = 0;
		while ((line_s[col] != '\0' || col < map->width) && line_s[0] != '\n')
		{
			set_map_value(map, line, col, line_s[col]);
			col++;
		}
		line++;
		line_list = line_list->next;
	}
	line_s = (char *) line_list->content;
	col = 0;
	while ((line_s[col] != '\0' || col < map->width) && line_s[0] != '\n')
	{
		set_map_value(map, line, col, line_s[col]);
		col++;
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
	while (temp->next != NULL)
	{
		res[i] = malloc((map->width + 1) * sizeof(t_cube_type));
		temp = temp->next;
		i++;
	}
	res[i] = malloc(map->width * sizeof(t_cube_type));
	temp = temp->next;
	return (res);
}

static t_file_content	*read_file(int fd, t_map *map,
							t_file_content *file_content)
{
	char	*str;

	map->width = 0;
	map->height = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (str != NULL && ft_strlen(str) > 0)
		{
			if (ft_strncmp(str, "NO", 2) == 0 || ft_strncmp(str, "SO", 2) == 0
				|| ft_strncmp(str, "WE", 2) == 0
				|| ft_strncmp(str, "EA", 2) == 0)
				ft_lstadd_back(&file_content->texture_lines, ft_lstnew(str));
			else if (str[0] == 'F' || str[0] == 'C')
				ft_lstadd_back(&file_content->f_c_lines, ft_lstnew(str));
			else
				ft_lstadd_back(&file_content->map_lines, ft_lstnew(str));
			if ((int) ft_strlen(str) - 1 > map->width)
				map->width = ft_strlen(str) - 1;
			map->height++;
		}
		str = get_next_line(fd);
	}
	return (file_content);
}
