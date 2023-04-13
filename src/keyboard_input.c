#include <cub3D.h>

void	escape_handler(void *arg)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static int	colission(t_window *window, char c, double speed, t_vector *dir)
{
	t_vector	future;

	if (c == 'x')
	{
		future.x = window->player->pos->x - dir->x * speed;
		future.y = window->player->pos->y;
	}
	else
	{
		future.x = window->player->pos->x;
		future.y = window->player->pos->y - dir->y * speed;
	}
	future.z = 0;
	if (get_cube_type(&future, window->map) != wall)
		return (0);
	else
		return (1);
}

static void	change_player_position(t_window *window, double angle)
{
	t_vector	dir;
	int			moved;

	dir.x = window->player->dir->x;
	dir.y = window->player->dir->y;
	rotate_hor_f(&dir, &dir, angle);
	moved = 0;
	if (!colission(window, 'x', SPEED, &dir))
	{
		window->player->pos->x -= dir.x * SPEED;
		moved = 1;
	}
	if (!colission(window, 'y', SPEED, &dir))
	{
		window->player->pos->y -= dir.y * SPEED;
		moved = 1;
	}
	if (moved)
		draw_scene(window);
}

void	player_movement(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
		change_player_position(window, 0);
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
		change_player_position(window, M_PI);
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
		change_player_position(window, M_PI_2);
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
		change_player_position(window, -M_PI_2);
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_E))
	{
		rotate_hor_f(window->player->dir, window->player->dir, 0.1f);
		draw_scene(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_Q))
	{
		rotate_hor_f(window->player->dir, window->player->dir, -0.1f);
		draw_scene(window);
	}
}
