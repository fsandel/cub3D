#include <cub3D.h>

static void	setup_enemy_textures(t_enemy **all_enemies);
static void	setup_singular_enemy(t_enemy *enemy);

t_enemy	**setup_enemy_struct(t_player *player, t_map *map)
{
	const int	amount = ft_lstsize(map->enemy_list);
	int			i;
	t_list		*head;
	t_enemy		**all_enemies;

	head = map->enemy_list;
	all_enemies = malloc((amount + 1) * sizeof(t_enemy *));
	i = 0;
	while (i < amount)
	{
		all_enemies[i] = malloc(sizeof(t_enemy));
		setup_singular_enemy(all_enemies[i]);
		all_enemies[i]->pos.x = ((t_vector *)(head->content))->x;
		all_enemies[i]->pos.y = ((t_vector *)(head->content))->y;
		set_enemy_dir(all_enemies[i], player);
		head = head->next;
		i++;
	}
	all_enemies[i] = NULL;
	ft_lstclear(&map->enemy_list, free);
	setup_enemy_textures(all_enemies);
	return (all_enemies);
}

static void	setup_singular_enemy(t_enemy *enemy)
{
	enemy->hitpoints = ENEMIE_HITPOINTS;
	enemy->frame_cooldown = ENEMY_FRAME_COOLDOWN;
	enemy->frame_count = 0;
	enemy->state = out_of_range;
	enemy->type = 0;
}

static bool	load_textures(t_enemy *enemy)
{
	enemy->tex_nb = 8;
	enemy->walking_tex[0][0] = mlx_load_png("textures/enemy/big_hans_blue/m0.png");
	enemy->walking_tex[0][1] = mlx_load_png("textures/enemy/big_hans_blue/m1.png");
	enemy->walking_tex[0][2] = mlx_load_png("textures/enemy/big_hans_blue/m2.png");
	enemy->walking_tex[0][3] = mlx_load_png("textures/enemy/big_hans_blue/m3.png");
	enemy->walking_tex[0][4] = mlx_load_png("textures/enemy/big_hans_blue/m4.png");
	enemy->walking_tex[0][5] = mlx_load_png("textures/enemy/big_hans_blue/m5.png");
	enemy->walking_tex[0][6] = mlx_load_png("textures/enemy/big_hans_blue/m6.png");
	enemy->walking_tex[0][7] = mlx_load_png("textures/enemy/big_hans_blue/m7.png");
	enemy->attacking_tex[0][0] = mlx_load_png("textures/enemy/big_hans_blue/a0.png");
	enemy->attacking_tex[0][1] = mlx_load_png("textures/enemy/big_hans_blue/a1.png");
	enemy->attacking_tex[0][2] = mlx_load_png("textures/enemy/big_hans_blue/a2.png");
	enemy->attacking_tex[0][3] = mlx_load_png("textures/enemy/big_hans_blue/a3.png");
	enemy->attacking_tex[0][4] = mlx_load_png("textures/enemy/big_hans_blue/a4.png");
	enemy->attacking_tex[0][5] = mlx_load_png("textures/enemy/big_hans_blue/a5.png");
	enemy->attacking_tex[0][6] = mlx_load_png("textures/enemy/big_hans_blue/a6.png");
	enemy->attacking_tex[0][7] = mlx_load_png("textures/enemy/big_hans_blue/a7.png");
	return (true);
}

static void	setup_enemy_textures(t_enemy **all_enemies)
{
	int		enemy_iter;
	int		tex_iter;
	t_enemy	tex_enemy;

	if (!all_enemies[0])
		return ;
	if (!load_textures(&tex_enemy))
		return ;
	enemy_iter = 0;
	while (all_enemies[enemy_iter])
	{
		tex_iter = 0;
		while (tex_iter < tex_enemy.tex_nb)
		{
			all_enemies[enemy_iter]->walking_tex[0][tex_iter]
				= tex_enemy.walking_tex[0][tex_iter];
			all_enemies[enemy_iter]->attacking_tex[0][tex_iter]
				= tex_enemy.attacking_tex[0][tex_iter];
			tex_iter++;
		}
		all_enemies[enemy_iter]->tex_nb = tex_enemy.tex_nb;
		enemy_iter++;
	}
}
