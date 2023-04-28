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

static void	setup_enemy_textures(t_enemy **all_enemies)
{
	int	i;
	int	j;

	if (!all_enemies[0])
		return ;
	all_enemies[0]->texture_nb = 2;
	all_enemies[0]->textures[0] = mlx_load_png("textures/rottmonk2.png");
	all_enemies[0]->textures[1] = mlx_load_png("textures/rottmonk2.png");
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
