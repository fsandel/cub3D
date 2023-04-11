#include <cub3D.h>

int	on_screen(int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (1);
	else
		return (0);
}

char	get_map_char(t_vector_f *pos, t_map *map)
{
	int	width;
	int	height;

	width = WIDTH / map->width;
	height = HEIGHT / map->heigth;
	if (pos->x > WIDTH || pos->x < 0)
		return ('1');
	if (pos->y > HEIGHT || pos->y < 0)
		return ('1');
	return (map->array[(int)pos->y / height][(int)pos->x / width]);
}
