#include <cub3D.h>

static void	setup_enemy_textures(t_enemy **all_enemies);
static void	setup_singular_enemy(t_enemy *enemy);

void	setup_enemy_struct(t_window *window, t_map *map)
{
	const int	amount = ft_lstsize(map->enemy_list);
	int			i;
	t_list		*head;

	head = map->enemy_list;
	window->all_enemies = malloc((amount + 1) * sizeof(t_enemy *));
	i = 0;
	while (i < amount)
	{
		window->all_enemies[i] = malloc(sizeof(t_enemy));
		setup_singular_enemy(window->all_enemies[i]);
		window->all_enemies[i]->pos.x = ((t_vector *)(head->content))->x;
		window->all_enemies[i]->pos.y = ((t_vector *)(head->content))->y;
		set_enemy_dir(window->all_enemies[i], window->player);
		head = head->next;
		i++;
	}
	window->all_enemies[i] = NULL;
	ft_lstclear(&map->enemy_list, free);
	setup_enemy_textures(window->all_enemies);
}

static void	setup_singular_enemy(t_enemy *enemy)
{
	enemy->hitpoints = ENEMIE_HITPOINTS;
	enemy->frame_cooldown = ENEMY_FRAME_COOLDOWN;
	enemy->frame_count = 0;
	enemy->state = out_of_range;
}

static void	load_textures(t_enemy *enemy)
{
	enemy->walking_texture_nb = 9;
	enemy->walking_textures[0] = mlx_load_png("textures/frames/zombie0.png");
	enemy->walking_textures[1] = mlx_load_png("textures/frames/zombie1.png");
	enemy->walking_textures[2] = mlx_load_png("textures/frames/zombie2.png");
	enemy->walking_textures[3] = mlx_load_png("textures/frames/zombie3.png");
	enemy->walking_textures[4] = mlx_load_png("textures/frames/zombie4.png");
	enemy->walking_textures[5] = mlx_load_png("textures/frames/zombie5.png");
	enemy->walking_textures[6] = mlx_load_png("textures/frames/zombie6.png");
	enemy->walking_textures[7] = mlx_load_png("textures/frames/zombie7.png");
	enemy->walking_textures[8] = mlx_load_png("textures/frames/zombie8.png");
	enemy->attacking_textures[0] = mlx_load_png("textures/frames/attack1.png");
	enemy->attacking_textures[1] = mlx_load_png("textures/frames/attack2.png");
	enemy->attacking_textures[2] = mlx_load_png("textures/frames/attack3.png");
	enemy->attacking_textures[3] = mlx_load_png("textures/frames/attack4.png");
	enemy->attacking_textures[4] = mlx_load_png("textures/frames/attack4.png");
	enemy->attacking_textures[5] = mlx_load_png("textures/frames/attack3.png");
	enemy->attacking_textures[6] = mlx_load_png("textures/frames/attack2.png");
	enemy->attacking_textures[7] = mlx_load_png("textures/frames/attack1.png");
	enemy->attacking_textures[8] = mlx_load_png("textures/frames/attack1.png");
	enemy->dead_textures[0] = mlx_load_png("textures/frames/dead.png");
}

static void	setup_enemy_textures(t_enemy **all_enemies)
{
	int	i;
	int	j;

	if (!all_enemies[0])
		return ;
	load_textures(all_enemies[0]);
	i = 1;
	while (all_enemies[i])
	{
		j = 0;
		while (j < all_enemies[0]->walking_texture_nb)
		{
			all_enemies[i]->walking_textures[j]
				= all_enemies[0]->walking_textures[j];
			all_enemies[i]->attacking_textures[j]
				= all_enemies[0]->attacking_textures[j];
			j++;
		}
		all_enemies[i]->dead_textures[0] = all_enemies[0]->dead_textures[0];
		all_enemies[i++]->walking_texture_nb
			= all_enemies[0]->walking_texture_nb;
	}
}