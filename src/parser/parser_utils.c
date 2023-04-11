#include <cub3D.h>

void	set_map_value(t_map *map, int line, int column, char c)
{
	if (c == '0')
		map->cubes[line][column] = walkable;
	else if (c == '1')
		map->cubes[line][column] = wall;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		map->cubes[line][column] = spawn;
	else
		map->cubes[line][column] = empty;
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
