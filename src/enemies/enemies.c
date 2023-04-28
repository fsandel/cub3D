#include <cub3D.h>

static void	check_enemies_state(t_window *window)
{
	(void)window;
}

static void	move_enemies(t_window *window)
{
	(void)window;
}

static void	draw_enemies(t_window *window)
{
	(void)window;
}

void	enemie_handler(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	check_enemies_state(window);
	move_enemies(window);
	draw_enemies(window);
}
