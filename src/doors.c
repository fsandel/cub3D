#include <cub3D.h>

static bool	toggle_targeted_door(t_window *window);

void	door_handler(t_window *window, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		if (toggle_targeted_door(window))
			window->redraw = true;
	}
}

static void	cast_iter_ray(t_window *window, t_vector dir, t_vector *target,
		t_cube_type target_type)
{
	const double	step_size = 0.01f;

	target->x = window->player->pos.x;
	target->y = window->player->pos.y;
	while (get_cube_type(target, window->map) < wall
		&& get_cube_type(target, window->map) != target_type)
	{
		target->x -= dir.x * step_size;
		target->y -= dir.y * step_size;
	}
}

static bool	interact_health_shelf(t_window *window, int x, int y)
{
	if (window->player->hp >= STARTING_HP)
		return (false);
	window->map->cubes[y][x] = health_empty;
	window->player->hp += HP_PICKUP;
	if (window->player->hp > STARTING_HP)
		window->player->hp = STARTING_HP;
	return (true);
}

static bool	interact_ammo_shelf(t_window *window, int x, int y)
{
	if (window->player->ammo >= STARTING_AMMO * 2)
		return (false);
	window->map->cubes[y][x] = ammo_empty;
	window->player->ammo += AMMO_PICKUP;
	if (window->player->ammo > STARTING_AMMO * 2)
		window->player->ammo = STARTING_AMMO * 2;
	return (true);
}

static bool	toggle_targeted_door(t_window *window)
{
	t_vector	target;
	double		dis;

	cast_iter_ray(window, window->player->dir, &target, door_open);
	dis = distance(window->player->pos, target);
	if (dis > COLLISION && dis < DOOR_TOUCH_RANGE)
	{
		if (get_cube_type(&target, window->map) == door_closed)
		{
			window->map->cubes[(int)target.y][(int)target.x] = door_open;
			return (true);
		}
		else if (get_cube_type(&target, window->map) == door_open)
		{
			window->map->cubes[(int)target.y][(int)target.x] = door_closed;
			return (true);
		}
		else if (get_cube_type(&target, window->map) == health_full)
			return (interact_health_shelf(window, target.x, target.y));
		else if (get_cube_type(&target, window->map) == ammo_full)
			return (interact_ammo_shelf(window, target.x, target.y));
		else if (get_cube_type(&target, window->map) == exit_cube)
			won_game(window);
	}
	return (false);
}
