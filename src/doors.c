#include <cub3D.h>

static void	toggle_surrounding_doors(t_window *window);

void	door_handler(mlx_key_data_t keydata, void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		toggle_surrounding_doors(window);
		draw_scene(window);
	}
}

static void	toggle_surrounding_doors(t_window *window)
{
	const int	pos_x = window->player->pos->x;
	const int	pos_y = window->player->pos->y;
	int			i;
	int			j;
	const int	range = 2;

	i = -range;
	while (i < range + 1)
	{
		j = -range;
		while (j < range + 1)
		{
			if (j == 0 && i == 0)
				(void)0;
			else if (window->map->cubes[pos_y + j][pos_x + i] == door_closed)
				window->map->cubes[pos_y + j][pos_x + i] = door_open;
			else if (window->map->cubes[pos_y + j][pos_x + i] == door_open)
				window->map->cubes[pos_y + j][pos_x + i] = door_closed;
			j++;
		}
		i++;
	}
}
