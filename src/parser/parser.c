#include "cub3D.h"

static t_map		*init_map(void);
static t_list		*read_file(int fd, t_map *map);
static void			populate_map(t_list *line_list, t_map *map);
static t_cube_type	**create_map(t_list *line_list, t_map *map);

t_map	*parse(int fd)
{
	t_list	*line_list;
	t_map	*map;

	map = init_map();
	line_list = read_file(fd, map);
	close(fd);
	map->cubes = NULL;
	map->cubes = create_map(line_list, map);
	populate_map(line_list, map);
	ft_lstclear(&line_list, &free);
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

static t_list	*read_file(int fd, t_map *map)
{
	char	*str;
	t_list	*lines;

	map->width = 0;
	map->height = 0;
	str = get_next_line(fd);
	lines = NULL;
	while (str != NULL)
	{
		if (str != NULL)
		{
			ft_lstadd_back(&lines, ft_lstnew(str));
			if ((int) ft_strlen(str) - 1 > map->width)
				map->width = ft_strlen(str) - 1;
			map->height++;
		}
		str = get_next_line(fd);
	}
	return (lines);
}
