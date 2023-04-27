#include <cub3D.h>

static bool	toggle_targeted_door(t_window *window);

void	door_handler(t_window *window, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (toggle_targeted_door(window))
			draw_scene(window);
	}
}

static void	cast_iter_ray(t_window *window, t_vector dir, t_vector *target,
		t_cube_type target_type)
{
	const double	step_size = 0.01f;

	target->x = window->player->pos->x;
	target->y = window->player->pos->y;
	while (get_cube_type(target, window->map) != wall
		&& get_cube_type(target, window->map) != door_closed
		&& get_cube_type(target, window->map) != target_type)
	{
		target->x -= dir.x * step_size;
		target->y -= dir.y * step_size;
	}
}

static bool	toggle_targeted_door(t_window *window)
{
	t_vector	target;
	double		dis;
	bool		redraw;

	redraw = false;
	cast_iter_ray(window, *window->player->dir, &target, door_open);
	dis = distance(*window->player->pos, target);
	if (dis > COLLISION && dis < DOOR_TOUCH_RANGE)
	{
		if (get_cube_type(&target, window->map) == door_closed)
		{
			window->map->cubes[(int)target.y][(int)target.x] = door_open;
			redraw = true;
		}
		else if (get_cube_type(&target, window->map) == door_open)
		{
			window->map->cubes[(int)target.y][(int)target.x] = door_closed;
			redraw = true;
		}
	}
	return (redraw);
}
