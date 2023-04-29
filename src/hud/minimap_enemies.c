#include <cub3D.h>

static void	draw_minimap_single_enemy(t_enemy *enemy, t_window *window)
{
	(void)window;
	(void)enemy;
}

void	draw_minimap_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		draw_minimap_single_enemy(window->all_enemies[i], window);
		i++;
	}
}
