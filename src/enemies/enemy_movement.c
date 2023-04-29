#include <cub3D.h>

static bool	move_single_enemy(t_enemy *enemy, t_map *map)
{
	t_vector	future_pos;
	bool		moved;

	moved = false;
	if (enemy->state != hunting)
		return (false);
	future_pos.x = enemy->pos.x - enemy->dir.x * 0.01;
	future_pos.y = enemy->pos.y;
	if (get_cube_type(&future_pos, map) != wall
		&& get_cube_type(&future_pos, map) != door_closed)
	{
		enemy->pos = future_pos;
		moved = true;
	}
	future_pos.x = enemy->pos.x;
	future_pos.y = enemy->pos.y - enemy->dir.y * 0.01;
	if (get_cube_type(&future_pos, map) != wall
		&& get_cube_type(&future_pos, map) != door_closed)
	{
		enemy->pos = future_pos;
		moved = true;
	}
	return (moved);
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
