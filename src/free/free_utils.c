#include <cub3D.h>

void	free_all_enemies(t_enemy **all_enemies)
{
	int	enemy_iter;
	int	tex_iter;

	tex_iter = 0;
	if (all_enemies[0])
	{
		while (tex_iter < all_enemies[0]->tex_nb)
		{
			mlx_delete_texture(all_enemies[0]->attacking_tex[tex_iter]);
			mlx_delete_texture(all_enemies[0]->walking_tex[tex_iter]);
			tex_iter++;
		}
		mlx_delete_texture(all_enemies[0]->dead_tex);
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
		mlx_delete_texture(weapon->gun_tex[i++]);
	i = 0;
	while (weapon->torch_tex[i])
		mlx_delete_texture(weapon->torch_tex[i++]);
	i = 0;
	while (weapon->muzzle_tex[i])
		mlx_delete_texture(weapon->muzzle_tex[i++]);
	free(weapon);
}

void	free_window(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	mlx_delete_texture(window->exit_tex[0]);
	mlx_delete_texture(window->exit_tex[1]);
	mlx_delete_texture(window->health_tex[0]);
	mlx_delete_texture(window->health_tex[1]);
	mlx_delete_texture(window->ammo_tex[0]);
	mlx_delete_texture(window->ammo_tex[1]);
	mlx_delete_texture(window->destructible_tex);
	mlx_terminate(window->mlx);
	free(window);
}

void	free_player(t_player *player)
{
	free_weapon(player->weapon);
	free(player);
}
