#include <cub3D.h>

static int	move_single_enemy(t_enemy *enemy, t_map *map)
{
	t_vector	future_pos;

	if (enemy->state != hunting)
		return (0);
	future_pos.x = enemy->pos.x - enemy->dir.x * 0.01;
	future_pos.y = enemy->pos.y - enemy->dir.y * 0.01;
	if (get_cube_type(&future_pos, map) != wall
		&& get_cube_type(&future_pos, map) != door_closed)
	{
		enemy->pos = future_pos;
		return (1);
	}
	return (0);
}

void	move_enemies(t_window *window)
{
	int	i;
	int	count_redraw;

	i = 0;
	count_redraw = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state != dead)
			count_redraw += move_single_enemy(window->all_enemies[i],
					window->map);
		i++;
	}
	if (count_redraw > 0)
		window->redraw = 1;
}
