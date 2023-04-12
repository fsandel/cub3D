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

	window = (t_window *)arg;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
	{
		window->player->pos->x -= window->player->dir->x * SPEED;
		window->player->pos->y -= window->player->dir->y * SPEED;
		draw_scene(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
	{
		window->player->pos->x += window->player->dir->x * SPEED;
		window->player->pos->y += window->player->dir->y * SPEED;
		draw_scene(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
	{
		rotate_hor_f(window->player->dir, window->player->dir, 0.1f);
		draw_scene(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
	{
		rotate_hor_f(window->player->dir, window->player->dir, -0.1f);
		draw_scene(window);
	}
}
