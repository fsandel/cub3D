#include <cub3D.h>

static void	setup_enemy_textures(t_enemy **all_enemies);

void	setup_enemy_struct(t_window *window, t_map *map)
{
	const int			amount = ft_lstsize(map->enemy_list);
	t_enemy				**all_enemies;
	int					i;
	t_list				*head;

	head = map->enemy_list;
	all_enemies = malloc((amount + 1) * sizeof(t_enemy *));
	i = 0;
	while (i < amount)
	{
		all_enemies[i] = malloc(sizeof(t_enemy));
		all_enemies[i]->hitpoints = ENEMIE_HITPOINTS;
		all_enemies[i]->hitpoints = 0;
		all_enemies[i]->state = out_of_range;
		all_enemies[i]->pos.x = ((t_vector *)(map->enemy_list->content))->x;
		all_enemies[i]->pos.y = ((t_vector *)(map->enemy_list->content))->y;
		set_enemy_dir(all_enemies[i], window->player);
		map->enemy_list = map->enemy_list->next;
		i++;
	}
	all_enemies[i] = NULL;
	ft_lstclear(&head, free);
	setup_enemy_textures(all_enemies);
	window->all_enemies = all_enemies;
}

static void	load_textures(t_enemy *enemy)
{
	enemy->texture_nb = 9;
	enemy->textures[0] = mlx_load_png("textures/frames/zombie0.png");
	enemy->textures[1] = mlx_load_png("textures/frames/zombie1.png");
	enemy->textures[2] = mlx_load_png("textures/frames/zombie2.png");
	enemy->textures[3] = mlx_load_png("textures/frames/zombie3.png");
	enemy->textures[4] = mlx_load_png("textures/frames/zombie4.png");
	enemy->textures[5] = mlx_load_png("textures/frames/zombie5.png");
	enemy->textures[6] = mlx_load_png("textures/frames/zombie6.png");
	enemy->textures[7] = mlx_load_png("textures/frames/zombie7.png");
	enemy->textures[8] = mlx_load_png("textures/frames/zombie8.png");
}

static void	setup_enemy_textures(t_enemy **all_enemies)
{
	int	i;
	int	j;

	if (!all_enemies[0])
		return ;
	load_textures(all_enemies[0]);
	i = 0;
	while (all_enemies[i])
	{
		j = 0;
		while (j < all_enemies[0]->texture_nb)
		{
			all_enemies[i]->textures[j] = all_enemies[0]->textures[j];
			j++;
		}
		all_enemies[i++]->texture_nb = all_enemies[0]->texture_nb;
	}
}
