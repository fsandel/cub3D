#include <cub3D.h>

static void	end_key_hook(mlx_key_data_t keydata, void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (keydata.action == MLX_PRESS)
		mlx_close_window(window->mlx);
}

void	check_dead(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->active == false)
		return ;
	if (window->player->hp <= 0)
	{
		window->active = false;
		mlx_set_instance_depth(window->img->instances, 4);
		draw_tex_to_screen(window->img, DEFEAT_SCREEN);
		mlx_key_hook(window->mlx, end_key_hook, window);
	}
}
