#include <cub3D.h>

static void	free_all_enemies(t_window *window)
{
	int	i;
	int	j;

	j = 0;
	if (window->all_enemies[0])
	{
		while (j < window->all_enemies[0]->walking_texture_nb)
		{
			mlx_delete_texture(window->all_enemies[0]->attacking_textures[j]);
			mlx_delete_texture(window->all_enemies[0]->walking_textures[j++]);
		}
		mlx_delete_texture(window->all_enemies[0]->dead_textures[0]);
	}
	i = 0;
	while (window->all_enemies[i])
		free(window->all_enemies[i++]);
	free(window->all_enemies);
}

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
	free(window->hud->minimap);
	free(window->hud);
}

void	free_window_struct(t_window *window)
{
	free_all_enemies(window);
	mlx_delete_image(window->mlx, window->img);
	mlx_delete_texture(window->map->textures[north]);
	mlx_delete_texture(window->map->textures[east]);
	mlx_delete_texture(window->map->textures[south]);
	mlx_delete_texture(window->map->textures[west]);
	if (window->map->door)
		mlx_delete_texture(window->map->door);
	mlx_terminate(window->mlx);
	free_cubes(window->map);
	free_hud(window);
	free(window->player);
	free(window->map->start_dir);
	free(window->map->start_pos);
	free(window->map);
	free(window);
}
