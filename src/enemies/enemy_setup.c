#include <cub3D.h>

static bool	setup_enemy_textures(t_enemy **all_enemies);
static void	setup_singular_enemy(t_enemy *enemy, t_vector *pos);
static void	free_prior_enemies(t_enemy **all_enemies, int amount);
int			enemy_load_png(t_enemy *enemy);
void		setup_enemy_type_speficic_values(t_enemy *enemy);

t_enemy	**setup_enemy_struct(t_player *player, t_map *map)
{
	const int	amount = ft_lstsize(map->enemy_list);
	int			i;
	t_list		*head;
	t_enemy		**all_enemies;

	head = map->enemy_list;
	all_enemies = malloc((amount + 1) * sizeof(t_enemy *));
	if (!all_enemies)
		return (NULL);
	i = 0;
	while (i < amount)
	{
		all_enemies[i] = malloc(sizeof(t_enemy));
		if (!all_enemies[i])
			return (free_prior_enemies(all_enemies, i), NULL);
		setup_singular_enemy(all_enemies[i], head->content);
		set_enemy_dir(all_enemies[i], player);
		head = head->next;
		i++;
	}
	all_enemies[i] = NULL;
	if (!setup_enemy_textures(all_enemies))
		return (NULL);
	ft_lstclear(&map->enemy_list, free);
	return (all_enemies);
}

static void	free_prior_enemies(t_enemy **all_enemies, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
		free(all_enemies[i++]);
	free(all_enemies);
}

static void	setup_singular_enemy(t_enemy *enemy, t_vector *pos)
{
	static t_enemy_type	type = 0;

	enemy->frame_cooldown = ENEMY_FRAME_COOLDOWN;
	enemy->frame_count = 0;
	enemy->state = out_of_range;
	enemy->pos.x = pos->x;
	enemy->pos.y = pos->y;
	enemy->type = type++;
	enemy->cooldown = 30;
	setup_enemy_type_speficic_values(enemy);
}

void	enemy_copy_tex_pointers(t_enemy *enemy, t_enemy *tex_enemy,
			int tex_iter)
{
	t_enemy_type	type;

	type = 0;
	while (type < 8)
	{
		enemy->walking_tex[type][tex_iter]
			= tex_enemy->walking_tex[type][tex_iter];
		enemy->attacking_tex[type][tex_iter]
			= tex_enemy->attacking_tex[type][tex_iter];
		type++;
	}
}

static bool	setup_enemy_textures(t_enemy **all_enemies)
{
	int				enemy_iter;
	int				tex_iter;
	t_enemy			tex_enemy;
	int				error;

	if (!all_enemies[0])
		return (true);
	error = enemy_load_png(&tex_enemy);
	enemy_iter = 0;
	while (all_enemies[enemy_iter])
	{
		tex_iter = 0;
		while (tex_iter < 8)
		{
			enemy_copy_tex_pointers(all_enemies[enemy_iter], &tex_enemy,
				tex_iter);
			tex_iter++;
		}
		all_enemies[enemy_iter]->tex_nb = 8;
		enemy_iter++;
	}
	if (error > 0)
		return (free_all_enemies(all_enemies), false);
	return (true);
}
