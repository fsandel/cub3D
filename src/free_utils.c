#include <cub3D.h>

void	free_map(t_cube_type **cube)
{
	int	i;

	i = 0;
	while (cube[i])
	{
		free(cube[i]);
		i++;
	}
	free(cube);
}

void	free_window_struct(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	mlx_terminate(window->mlx);
	free_map(window->map->cubes);
	free(window->player->dir);
	free(window->player->pos);
	free(window->player);
	free(window->map->start_dir);
	free(window->map->start_pos);
	free(window->map);
	free(window);
}
