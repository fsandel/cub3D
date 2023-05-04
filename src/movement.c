#include <cub3D.h>

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
	if (get_cube_type(&future_pos, window->map) < wall)
		return (false);
	else
		return (true);
}

static	double	get_speed(t_window *window)
{
	double	speed;

	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT_SHIFT)
		&& mlx_is_key_down(window->mlx, MLX_KEY_W))
		speed = SPRINT_SPEED;
	else
		speed = SPEED;
	if (DYNAMIC_SPEED == true)
		speed *= 60.0f / window->hud->fps->fps_num;
	return (speed);
}

bool	change_player_position(t_window *window, double angle)
{
	t_vector		dir;
	bool			moved;
	const double	speed = get_speed(window);

	dir.x = window->player->dir->x;
	dir.y = window->player->dir->y;
	rotate(&dir, &dir, angle);
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

bool	rotate_camera(t_window *window, double turn_speed)
{
	if (DYNAMIC_TURN_SPEED == true)
		turn_speed *= 60.0f / window->hud->fps->fps_num;
	rotate(window->player->dir, window->player->dir, turn_speed);
	return (true);
}
