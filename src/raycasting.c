#include <cub3D.h>

static t_direction	cast_ray(t_vector *pos, t_vector *dir,
						t_vector *target, t_map *map);
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
		direction = cast_ray(window->player->pos, &ray_dir,
				&target, window->map);
		draw_vertical_line(window, &target, ray_iter + WIDTH / 2, direction);
		ray_iter++;
	}
}

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
			mlx_put_pixel(window->img, p_x, p_y++, pix);
		}
	}
}

//make sure this thinking is correct, my thought is you always should hit now
static void	set_target(t_vector *target, t_vector *pos, t_vector *dir, int i)
{
	target->x = pos->x - (i * dir->x * SPEED);
	target->y = pos->y - (i * dir->y * SPEED);
}

static t_direction	get_direction(t_vector *dir, char c)
{
	t_direction	direction;

	if (c == 'x')
	{
		if (dir->x > 0)
			direction = east;
		else
			direction = west;
	}
	else
	{
		if (dir->y > 0)
			direction = south;
		else
			direction = north;
	}
	return (direction);
}
double	get_s_x(double d_x, double d_y)
{
	if (d_x == 0)
		return (1);
	return (sqrt(1 + (d_y * d_y / d_x / d_x)));
}

double	get_s_y(double d_x, double d_y)
{
	if (d_y == 0)
		return (1);
	return (sqrt(1 + (d_x * d_x / d_y / d_y)));
}

static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	(void)pos;
	(void)dir;
	(void)target;
	(void)map;
	return (0);
}

static t_direction	cast_ray(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	int			i;
	t_vector	temp;
	t_direction	direction;

	temp = (t_vector){pos->x, pos->y, pos->z};
	i = 0;
	direction = north;
	while (temp.x < map->width && temp.y < map->height)
	{
		temp.x = pos->x - i * (dir->x * SPEED);
		if (get_cube_type(&temp, map) == wall)
		{
			direction = get_direction(dir, 'x');
			break ;
		}
		temp.y = pos->y - i * (dir->y * SPEED);
		if (get_cube_type(&temp, map) == wall)
		{
			direction = get_direction(dir, 'y');
			break ;
		}
		i++;
	}
	return (set_target(target, pos, dir, i), direction);
}
