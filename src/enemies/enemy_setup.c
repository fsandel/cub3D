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

static void	setup_enemy_textures(t_enemy **all_enemies)
{
	int		i;
	int		j;
	t_enemy	tex_enemy;

	if (!all_enemies[0])
		return ;
	if (!load_textures(&tex_enemy))
		return ;
	i = 0;
	while (all_enemies[i])
	{
		j = 0;
		while (j < all_enemies[0]->tex_nb)
		{
			all_enemies[i]->walking_tex[j] = tex_enemy.walking_tex[j];
			all_enemies[i]->attacking_tex[j] = tex_enemy.attacking_tex[j];
			j++;
		}
		all_enemies[i]->dead_tex = tex_enemy.dead_tex;
		all_enemies[i++]->tex_nb = tex_enemy.tex_nb;
	}
}
