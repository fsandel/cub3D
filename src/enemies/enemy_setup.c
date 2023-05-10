#include <cub3D.h>

static bool	setup_enemy_textures(t_enemy **all_enemies);
static void	setup_singular_enemy(t_enemy *enemy, t_vector *pos);
static void	free_prior_enemies(t_enemy **all_enemies, int amount);

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
	enemy->hitpoints = ENEMIE_HITPOINTS;
	enemy->frame_cooldown = ENEMY_FRAME_COOLDOWN;
	enemy->frame_count = 0;
	enemy->state = out_of_range;
	enemy->pos.x = pos->x;
	enemy->pos.y = pos->y;
}

static bool	load_textures(t_enemy *enemy)
{
	enemy->tex_nb = 9;
	enemy->walking_tex[0] = mlx_load_png("textures/enemy/zombie0.png");
	enemy->walking_tex[1] = mlx_load_png("textures/enemy/zombie1.png");
	enemy->walking_tex[2] = mlx_load_png("textures/enemy/zombie2.png");
	enemy->walking_tex[3] = mlx_load_png("textures/enemy/zombie3.png");
	enemy->walking_tex[4] = mlx_load_png("textures/enemy/zombie4.png");
	enemy->walking_tex[5] = mlx_load_png("textures/enemy/zombie5.png");
	enemy->walking_tex[6] = mlx_load_png("textures/enemy/zombie6.png");
	enemy->walking_tex[7] = mlx_load_png("textures/enemy/zombie7.png");
	enemy->walking_tex[8] = mlx_load_png("textures/enemy/zombie8.png");
	enemy->attacking_tex[0] = mlx_load_png("textures/enemy/attack1.png");
	enemy->attacking_tex[1] = mlx_load_png("textures/enemy/attack2.png");
	enemy->attacking_tex[2] = mlx_load_png("textures/enemy/attack3.png");
	enemy->attacking_tex[3] = mlx_load_png("textures/enemy/attack4.png");
	enemy->attacking_tex[4] = mlx_load_png("textures/enemy/attack4.png");
	enemy->attacking_tex[5] = mlx_load_png("textures/enemy/attack3.png");
	enemy->attacking_tex[6] = mlx_load_png("textures/enemy/attack2.png");
	enemy->attacking_tex[7] = mlx_load_png("textures/enemy/attack1.png");
	enemy->attacking_tex[8] = mlx_load_png("textures/enemy/attack1.png");
	enemy->dead_tex = mlx_load_png("textures/enemy/dead.png");
	return (true);
}

static bool	setup_enemy_textures(t_enemy **all_enemies)
{
	int		enemy_iter;
	int		tex_iter;
	t_enemy	tex_enemy;

	if (!all_enemies[0])
		return (true);
	if (!load_textures(&tex_enemy))
		return (false);
	enemy_iter = 0;
	while (all_enemies[enemy_iter])
	{
		tex_iter = 0;
		while (tex_iter < tex_enemy.tex_nb)
		{
			all_enemies[enemy_iter]->walking_tex[tex_iter]
				= tex_enemy.walking_tex[tex_iter];
			all_enemies[enemy_iter]->attacking_tex[tex_iter]
				= tex_enemy.attacking_tex[tex_iter];
			tex_iter++;
		}
		all_enemies[enemy_iter]->dead_tex = tex_enemy.dead_tex;
		all_enemies[enemy_iter]->tex_nb = tex_enemy.tex_nb;
		enemy_iter++;
	}
	return (true);
}
