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
		future_pos.x = window->player->pos->x - dir->x * speed
			- COLLISION * sign(dir->x);
		future_pos.y = window->player->pos->y;
	}
	else
	{
		future_pos.x = window->player->pos->x;
		future_pos.y = window->player->pos->y - dir->y * speed
			- COLLISION * sign(dir->y);
	}
	future_pos.z = 0;
	if (get_cube_type(&future_pos, window->map) != wall
		&& get_cube_type(&future_pos, window->map) != door_closed)
		return (false);
	else
		return (true);
}

static	double	get_speed(t_window *window)
{
	double	speed;

	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT_SHIFT))
		speed = SPRINT_SPEED;
	else
		speed = SPEED;
	//speed *= 60 / window->hud->fps->fps_num;
	return (speed);
}

static bool	change_player_position(t_window *window, double angle)
{
	t_vector		dir;
	bool			moved;
	const double	speed = get_speed(window);

	dir.x = window->player->dir->x;
	dir.y = window->player->dir->y;
	rotate_hor_f(&dir, &dir, angle);
	moved = false;
	if (!colission(window, 'x', speed, &dir))
	{
		window->player->pos->x -= dir.x * speed;
		moved = true;
	}
	if (!colission(window, 'y', speed, &dir))
	{
		window->player->pos->y -= dir.y * speed;
		moved = true;
	}
	return (moved);
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
	{
		rotate_hor_f(window->player->dir, window->player->dir, TURN_SPEED);
		redraw = true;
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(window->mlx, MLX_KEY_Q))
	{
		rotate_hor_f(window->player->dir, window->player->dir, -TURN_SPEED);
		redraw = true;
	}
	if (redraw == true)
		draw_scene(window);
}
