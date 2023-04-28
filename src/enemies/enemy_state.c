#include <cub3D.h>

static void	set_single_enemie_state(t_enemy *enemy, t_player *player, t_map *map)
{
	//t_vector	tmp_pos;
	(void)map;
	set_enemy_dir(enemy, player);
}

void	check_enemies_state(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		set_single_enemie_state(window->all_enemies[i], window->player, window->map);
		i++;
	}
}
