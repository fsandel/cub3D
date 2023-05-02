#include <cub3D.h>

static void	sort_enemies(t_window *window)
{
	t_enemy	*temp;
	int		i;

	i = 0;
	while (window->all_enemies[i] && window->all_enemies[i + 1])
	{
		if (window->all_enemies[i]->dis < window->all_enemies[i + 1]->dis)
		{
			temp = window->all_enemies[i];
			window->all_enemies[i] = window->all_enemies[i + 1];
			window->all_enemies[i + 1] = temp;
		}
		i++;
	}
}

void	enemie_handler(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->active == false)
		return ;
	check_enemies_state(window);
	move_enemies(window);
	sort_enemies(window);
	draw_enemies(window);
	attack_enemies(window);
}
