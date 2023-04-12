#include <cub3D.h>

void	escape_handler(void *arg)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static int	colission(t_window *window, char c, double speed)
{
	t_vector	future;

	if (c == 'x')
	{
		future.x = window->player->pos->x - window->player->dir->x * speed;
		future.y = window->player->pos->y;
	}
	else
	{
		future.x = window->player->pos->x;
		future.y = window->player->pos->y - window->player->dir->y * speed;
	}
	future.z = 0;
	if (get_cube_type(&future, window->map) == walkable)
		return (0);
	else
		return (1);
}

static void	change_player_position(t_window *window, double speed)
{
	if (!colission(window, 'x', speed))
	{
		window->player->pos->x -= window->player->dir->x * speed;
		draw_scene(window);
	}
	if (!colission(window, 'y', speed))
	{
		window->player->pos->y -= window->player->dir->y * speed;
		draw_scene(window);
	}
}

void	player_movement(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
		change_player_position(window, SPEED);
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
		change_player_position(window, -SPEED);
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
