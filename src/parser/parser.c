#include "cub3D.h"

static t_list			*read_file(int fd, t_map *map);
static void				populate_map(t_list *line_list, t_map *map);
static t_square_type	**create_map(t_list *line_list, t_map *map);

int	parse(int fd)
{
	t_list	*line_list;
	t_map	*map;

	map = malloc(sizeof(map));
	if (!map)
		return (EXIT_FAILURE);
	line_list = read_file(fd, map);
	close(fd);
	print_file(line_list);
	ft_printf("line count: %d\ncolumn cout: %d\n", map->height, map->width);
	map->square = NULL;
	map->square = create_map(line_list, map);
	populate_map(line_list, map);
	ft_lstclear(&line_list, &free);
	free(map);
	return (EXIT_SUCCESS);
}

static void	populate_map(t_list *line_list, t_map *map)
{
	int		line;
	int		column;
	t_list	*temp;
	char	*line_str;

	line = 0;
	temp = line_list;
	while (temp->next != NULL)
	{
		line_str = (char *) temp->content;
		column = 0;
		while ((line_str[column] != '\0' || column < map->width)
			&& line_str[column] != '\n' && line_str[0] != '\n')
		{
			set_map_value(map, line, column, line_str[column]);
			column++;
		}
		line++;
		temp = temp->next;
	}
	while (line_str[column] != '\0' || column < map->width)
	{
		set_map_value(map, line, column, line_str[column]);
		column++;
	}
}

static t_square_type	**create_map(t_list *line_list, t_map *map)
{
	t_list			*temp;
	t_square_type	**res;
	int				i;

	res = malloc(map->height * sizeof(t_square_type *));
	if (!res)
		return (NULL);
	temp = line_list;
	i = 0;
	while (temp->next != NULL)
	{
		res[i] = malloc(map->width * sizeof(t_square_type));
		temp = temp->next;
		i++;
	}
	res[i] = malloc(map->width * sizeof(t_square_type));
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
