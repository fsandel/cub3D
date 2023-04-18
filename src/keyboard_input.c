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
	t_vector	future_pos;

	if (c == 'x')
	{
		future_pos.x = window->player->pos->x - dir->x * speed;
		future_pos.y = window->player->pos->y;
	}
	else
	{
		future_pos.x = window->player->pos->x;
		future_pos.y = window->player->pos->y - dir->y * speed;
	}
	future_pos.z = 0;
	if (get_cube_type(&future_pos, window->map) != wall)
		return (false);
	else
		return (true);
}

static void	change_player_position(t_window *window, double angle)
{
	t_vector	dir;
	bool		moved;

	dir.x = window->player->dir->x;
	dir.y = window->player->dir->y;
	rotate_hor_f(&dir, &dir, angle);
	moved = false;
	if (!colission(window, 'x', SPEED, &dir))
	{
		window->player->pos->x -= dir.x * SPEED;
		moved = true;
	}
	if (!colission(window, 'y', SPEED, &dir))
	{
		window->player->pos->y -= dir.y * SPEED;
		moved = true;
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
		rotate_hor_f(window->player->dir, window->player->dir, TURN_SPEED);
		draw_scene(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_Q))
	{
		rotate_hor_f(window->player->dir, window->player->dir, -TURN_SPEED);
		draw_scene(window);
	}
}
