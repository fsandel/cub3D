#include <cub3D.h>

void	escape_handler(void *arg)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

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
