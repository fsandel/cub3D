#include <cub3D.h>

void	enemie_handler(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	check_enemies_state(window);
	move_enemies(window);
	draw_enemies(window);
}
