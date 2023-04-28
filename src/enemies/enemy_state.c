#include <cub3D.h>

static void	set_single_enemie_state(t_enemy *enemy, t_player *player,
	t_map *map)
{
	t_vector	tmp_pos;
	double		dis;

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
	if (dis < 0.5 && dis < ENEMY_RANGE)
		enemy->state = hunting;
	else if (dis < 0.5)
		enemy->state = waiting;
	else
		enemy->state = out_of_range;
}

void	check_enemies_state(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state != dead)
			set_single_enemie_state(window->all_enemies[i], window->player,
				window->map);
		i++;
	}
}
