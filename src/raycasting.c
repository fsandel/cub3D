#include <cub3D.h>

// static t_direction	cast_ray(t_vector *pos, t_vector *dir,
// 						t_vector *target, t_map *map);
static void			draw_vertical_line(t_window *window, t_vector *target,
						int i, t_direction direction);
static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
						t_vector *target, t_map *map);

void	draw_scene(t_window *window)
{
	t_vector			target;
	t_vector			ray_dir;
	const double		fov = (FOV * M_PI) / 180;
	int					ray_iter;
	t_direction			direction;

	ray_iter = -WIDTH / 2;
	while (ray_iter < WIDTH / 2)
	{
		rotate_hor_f(window->player->dir, &ray_dir, ray_iter * fov / WIDTH);
		direction = cast_ray_dda(window->player->pos, &ray_dir,
				&target, window->map);
		if (ray_iter == 0)
			printf("distance: %f\n", distance(*window->player->pos, target));
		draw_vertical_line(window, &target, ray_iter + WIDTH / 2, direction);
		ray_iter++;
	}
}

// void	draw_scene(t_window *window)
// {
// 	t_vector			target;
// 	t_vector			ray_dir;
// 	const double		fov = (FOV * M_PI) / 180;
// 	int					ray_iter;
// 	t_direction			direction;

// 	ray_iter = -WIDTH / 2;
// 	while (ray_iter < WIDTH / 2)
// 	{
// 		rotate_hor_f(window->player->dir, &ray_dir, ray_iter * fov / WIDTH);
// 		direction = cast_ray_dda(window->player->pos, &ray_dir,
// 				&target, window->map);
// 		if (ray_iter == 0)
// 			printf("distance: %f\n", distance(*window->player->pos, target));
// 		draw_vertical_line(window, &target, ray_iter + WIDTH / 2, direction);
// 		ray_iter++;
// 	}
// }

static void	draw_vertical_line(t_window *window, t_vector *target, int p_x,
				t_direction direction)
{
	const double	line_height = HEIGHT * 1 / distance_perpendicular(
			*window->player->pos, *window->player->dir, *target);
	const int		start = max(((HEIGHT - line_height) / 2), 0);
	int				p_y;
	uint32_t		pix;
	t_vector		tex;

	p_y = 0;
	while (p_y < HEIGHT)
	{
		if (p_y < start)
			mlx_put_pixel(window->img, p_x, p_y++, window->map->ceiling_color);
		else if (p_y >= start + line_height - 1)
			mlx_put_pixel(window->img, p_x, p_y++, window->map->floor_color);
		else
		{
			tex.x = texture_x_value(window->map->textures[direction],
					target, direction);
			tex.y = texture_y_value(window->map->textures[direction],
					line_height, p_y, start);
			pix = get_rgba_from_tex(window->map->textures[direction],
					tex.x, tex.y);
			(void)pix;
			mlx_put_pixel(window->img, p_x, p_y++, RED);
		}
	}
}

//make sure this thinking is correct, my thought is you always should hit now
// static void	set_target(t_vector *target, t_vector *pos, t_vector *dir, int i)
// {
// 	target->x = pos->x - (i * dir->x * SPEED);
// 	target->y = pos->y - (i * dir->y * SPEED);
// }

// static t_direction	get_direction(t_vector *dir, char c)
// {
// 	t_direction	direction;

// 	if (c == 'x')
// 	{
// 		if (dir->x > 0)
// 			direction = east;
// 		else
// 			direction = west;
// 	}
// 	else
// 	{
// 		if (dir->y > 0)
// 			direction = south;
// 		else
// 			direction = north;
// 	}
// 	return (direction);
// }
double	get_sx(double dx, double dy)
{
	if (dx == 0)
		return (1);
	return (sqrt(1 + (dy * dy / dx / dx)));
}

double	get_sy(double dx, double dy)
{
	if (dy == 0)
		return (1);
	return (sqrt(1 + (dx * dx / dy / dy)));
}

static void	set_dx_and_dy(double *dx, double *dy, t_vector *dir, t_vector *pos)
{
	if (dir->x > 0 && dir->y > 0)
	{
		*dx = 1 - ft_modf(pos->x);
		*dy = 1 - ft_modf(pos->y);
	}
	else if (dir->x > 0 && dir->y < 0)
	{
		*dx = 1 - ft_modf(pos->x);
		*dy = ft_modf(pos->y);
	}
	else if (dir->x < 0 && dir->y > 0)
	{
		*dx = ft_modf(pos->x);
		*dy = 1 - ft_modf(pos->y);
	}
	else
	{
		*dx = ft_modf(pos->x);
		*dy = ft_modf(pos->y);
	}
}

static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	t_vector	temp_dir;

	set_vec(target, pos->x, pos->y, pos->z);
	set_vec(&temp_dir, dir->x, dir->y, dir->z);
	while (get_cube_type(target, map) != wall)
	{
		set_dx_and_dy(&dx, &dy, dir, target);
		sx = get_sx(dx, dy);
		sy = get_sy(dx, dy);
		if (sx < sy)
			norm(&temp_dir, sx);
		else
			norm(&temp_dir, sy);
		set_vec(target, target->x - temp_dir.x, target->y - temp_dir.y, target->z - temp_dir.z);
	}
	//remember to return the right direction
	return (0);
}

// static t_direction	cast_ray(t_vector *pos, t_vector *dir,
// 	t_vector *target, t_map *map)
// {
// 	int			i;
// 	t_vector	temp;
// 	t_direction	direction;

// 	temp = (t_vector){pos->x, pos->y, pos->z};
// 	i = 0;
// 	direction = north;
// 	while (temp.x < map->width && temp.y < map->height)
// 	{
// 		temp.x = pos->x - i * (dir->x * SPEED);
// 		if (get_cube_type(&temp, map) == wall)
// 		{
// 			direction = get_direction(dir, 'x');
// 			break ;
// 		}
// 		temp.y = pos->y - i * (dir->y * SPEED);
// 		if (get_cube_type(&temp, map) == wall)
// 		{
// 			direction = get_direction(dir, 'y');
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (set_target(target, pos, dir, i), direction);
// }
