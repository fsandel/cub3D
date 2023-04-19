#include <cub3D.h>

void	free_cubes(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->cubes[i]);
		i++;
	}
	free(map->cubes);
}

static void	free_hud(t_window *window)
{
	free(window->hud->fps);
	free(window->hud);
}

void	free_window_struct(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	mlx_delete_texture(window->map->textures[north]);
	mlx_delete_texture(window->map->textures[east]);
	mlx_delete_texture(window->map->textures[south]);
	mlx_delete_texture(window->map->textures[west]);
	mlx_terminate(window->mlx);
	free_cubes(window->map);
	free_hud(window);
	free(window->player);
	free(window->map->start_dir);
	free(window->map->start_pos);
	free(window->map);
	free(window);
}
