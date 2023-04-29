#include <cub3D.h>

static void	set_single_enemie_state(t_enemy *enemy, t_player *player,
	t_map *map)
{
	t_vector	tmp_pos;
	double		dis;

	dis = 5;
	set_enemy_dir(enemy, player);
	tmp_pos.x = enemy->pos.x;
	tmp_pos.y = enemy->pos.y;
	while (get_cube_type(&tmp_pos, map) != wall
		&& get_cube_type(&tmp_pos, map) != door_closed)
	{
		tmp_pos.x -= enemy->dir.x * 0.01;
		tmp_pos.y -= enemy->dir.y * 0.01;
		dis = distance(tmp_pos, *player->pos);
		if (dis < 0.1)
			break ;
	}
	enemy->dis = distance(*player->pos, enemy->pos);
	if (dis < 0.5 && enemy->dis < 1)
		enemy->state = attacking;
	else if (dis < 0.5 && enemy->dis < ENEMY_RANGE)
		enemy->state = hunting;
	else if (dis < 0.5)
		enemy->state = waiting;
	else
		enemy->state = out_of_range;
}

static void	update_meta_data(t_enemy *enemy, t_player *player, t_window *window)
{
	enemy->delta_angle = atan2(-(enemy->dir.x), -(enemy->dir.y))
		- atan2((player->dir->x), (player->dir->y));
	enemy->brightness = max(1.0 - (enemy->dis / window->fog), 0);
	if (enemy->hitpoints <= 0)
		enemy->state = dead;
}

void	check_enemies_state(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		set_single_enemie_state(window->all_enemies[i], window->player,
			window->map);
		update_meta_data(window->all_enemies[i], window->player, window);
		i++;
	}
}
