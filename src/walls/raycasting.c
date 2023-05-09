#include <cub3D.h>

void				draw_vertical_line(t_window *window, t_vector *target,
						int p_x, t_direction direction);
static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
						t_vector *target, t_map *map);

void	draw_scene(t_window *window)
{
	t_vector			target;
	t_vector			ray_dir;
	const double		fov = (FOV * M_PI) / 180;
	int					ray_iter;
	t_direction			dir;

	ray_iter = -WIDTH / 2;
	while (ray_iter < WIDTH / 2)
	{
		rotate(&window->player->dir, &ray_dir, ray_iter * fov / WIDTH);
		dir = cast_ray_dda(&window->player->pos, &ray_dir,
				&target, window->map);
		draw_vertical_line(window, &target, ray_iter + WIDTH / 2, dir);
		ray_iter++;
	}
}

static void	set_dx_and_dy(double *dx, double *dy, t_vector *dir, t_vector *pos)
{
	if (dir->x >= 0 && dir->y >= 0)
	{
		*dx = -ft_modf(pos->x);
		*dy = -ft_modf(pos->y);
	}
	else if (dir->x >= 0 && dir->y < 0)
	{
		*dx = -ft_modf(pos->x);
		*dy = 1 - ft_modf(pos->y);
	}
	else if (dir->x < 0 && dir->y >= 0)
	{
		*dx = 1 - ft_modf(pos->x);
		*dy = -ft_modf(pos->y);
	}
	else
	{
		*dx = 1 - ft_modf(pos->x);
		*dy = 1 - ft_modf(pos->y);
	}
}

static t_direction	get_direction_of_target(t_vector old, t_vector target)
{
	if (old.x >= floor(target.x) && old.x < ceil(target.x))
	{
		if (old.y >= floor(target.y))
			return (south);
		else
			return (north);
	}
	else
	{
		if (old.x >= floor(target.x))
			return (east);
		else
			return (west);
	}
}

static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	double		dx;
	double		dy;
	double		angle;
	t_vector	old;

	set_vec(target, pos->x, pos->y);
	while (get_cube_type(target, map) < wall)
	{
		set_dx_and_dy(&dx, &dy, dir, target);
		angle = atan2(dir->y, dir->x);
		norm(dir, min(dx / -cos(angle), dy / -sin(angle)) * 1.000001);
		set_vec(&old, target->x, target->y);
		set_vec(target, target->x - dir->x, target->y - dir->y);
	}
	norm(dir, 1);
	return (get_direction_of_target(old, *target));
}
