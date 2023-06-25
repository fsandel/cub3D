#include <cub3D.h>

static void	set_single_enemie_state(t_enemy *enemy, t_player *player,
	t_map *map)
{
	t_vector	tmp_pos;

	set_enemy_dir(enemy, player);
	tmp_pos.x = enemy->pos.x;
	tmp_pos.y = enemy->pos.y;
	while (distance(tmp_pos, player->pos) > 0.2)
	{
		tmp_pos.x -= enemy->dir.x * 0.01;
		tmp_pos.y -= enemy->dir.y * 0.01;
		if (get_cube_type(&tmp_pos, map) >= wall)
			return (enemy->state = out_of_range, (void)0);
	}
	enemy->dis = distance(player->pos, enemy->pos);
	if (enemy->dis < enemy->range)
		enemy->state = attacking;
	else if (enemy->dis < ENEMY_RANGE)
		enemy->state = hunting;
	else
		enemy->state = waiting;
}

static void	update_meta_data(t_enemy *enemy, t_player *player, t_window *window)
{
	enemy->delta_angle = atan2(-(enemy->dir.x), -(enemy->dir.y))
		- atan2((player->dir.x), (player->dir.y));
	if (enemy->delta_angle < -M_PI)
		enemy->delta_angle += 2 * M_PI;
	enemy->brightness = max(1.0 - (enemy->dis / window->fog), 0);
	if (enemy->hp <= 0 && enemy->state != out_of_range)
		enemy->state = dead;
	enemy->x_on_screen = WIDTH * (1 - sin(enemy->delta_angle)
			/ sin(FOV * M_PI / 360)) / 2;
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
