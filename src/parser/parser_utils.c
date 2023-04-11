#include <cub3D.h>

void	set_map_value(t_map *map, int line, int column, char c)
{
	if (c == '0')
		map->square[line][column] = floor;
	else if (c == '1')
		map->square[line][column] = wall;
	else
		map->square[line][column] = empty;
}

void	print_file(t_list *line_list)
{
	t_list	*temp;

	temp = line_list;
	while (temp->next != NULL)
	{
		ft_printf("%s", temp->content);
		temp = temp->next;
	}
	ft_printf("%s\n", temp->content);
}
