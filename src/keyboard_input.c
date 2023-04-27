#include <cub3D.h>

static void	escape_handler(t_window *window, mlx_key_data_t keydata);
static void	zoom_minimap(t_window *window, mlx_key_data_t keydata);

void	player_movement(void *arg)
{
	t_window	*window;
	bool		redraw;

	redraw = false;
	window = (t_window *)arg;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
		redraw = change_player_position(window, 0);
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
		redraw = change_player_position(window, M_PI);
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
		redraw = change_player_position(window, M_PI_2);
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
		redraw = change_player_position(window, -M_PI_2);
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_E))
		redraw = rotate_camera(window, TURN_SPEED);
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_Q))
		redraw = rotate_camera(window, -TURN_SPEED);
	if (redraw == true)
		draw_scene(window);
}

void	cub_key_hook(mlx_key_data_t keydata, void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	zoom_minimap(window, keydata);
	escape_handler(window, keydata);
	door_handler(window, keydata);
}

static void	zoom_minimap(t_window *window, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_PAGE_UP && keydata.action == MLX_PRESS)
	{
		if (window->hud->minimap->zoom < 10)
			window->hud->minimap->zoom++;
	}
	if (keydata.key == MLX_KEY_PAGE_DOWN && keydata.action == MLX_PRESS)
	{
		if (window->hud->minimap->zoom > 2)
			window->hud->minimap->zoom--;
	}
}

static void	escape_handler(t_window *window, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(window->mlx);
}
