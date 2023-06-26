#include <cub3D.h>

void	free_texture_array(int first_max, int second_max,
			mlx_texture_t *array[first_max][second_max]);

void	free_all_enemies(t_enemy **all_enemies)
{
	int	enemy_iter;

	if (all_enemies[0])
	{
		free_texture_array(8, 8, all_enemies[0]->attacking_tex);
		free_texture_array(8, 8, all_enemies[0]->walking_tex);
		free_texture_array(8, 4, all_enemies[0]->death_tex);
	}
	enemy_iter = 0;
	while (all_enemies[enemy_iter])
		free(all_enemies[enemy_iter++]);
	free(all_enemies);
}

void	free_cubes(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height && map->cubes[i])
	{
		free(map->cubes[i]);
		i++;
	}
	free(map->cubes);
}

void	free_weapon(t_weapon *weapon)
{
	int	i;

	i = 0;
	while (weapon->gun_tex[i])
		ft_mlx_delete_texture(weapon->gun_tex[i++]);
	i = 0;
	while (weapon->torch_tex[i])
		ft_mlx_delete_texture(weapon->torch_tex[i++]);
	i = 0;
	free(weapon);
}

void	free_window(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	ft_mlx_delete_texture(window->exit_tex[0]);
	ft_mlx_delete_texture(window->exit_tex[1]);
	ft_mlx_delete_texture(window->health_tex[0]);
	ft_mlx_delete_texture(window->health_tex[1]);
	ft_mlx_delete_texture(window->ammo_tex[0]);
	ft_mlx_delete_texture(window->ammo_tex[1]);
	ft_mlx_delete_texture(window->destructible_tex);
	mlx_terminate(window->mlx);
	free(window);
}

void	free_player(t_player *player)
{
	free_weapon(player->weapon);
	free(player);
}
