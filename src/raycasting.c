#include <cub3D.h>

static int	cast_ray(t_vector *pos, t_vector *dir,
				t_vector *target, t_map *map);
static void	draw_vertical_line(t_window *window, t_vector *target, int i,
				enum e_direction direction);

uint32_t	get_pixel(mlx_texture_t *tex, int x, int y);

void	draw_scene(t_window *window)
{
	t_vector			target;
	t_vector			dir;
	const double		fov = (FOV * M_PI) / 180;
	int					i;
	enum e_direction	direction;

	i = -WIDTH / 2;
	while (i < WIDTH / 2)
	{
		rotate_hor_f(window->player->dir, &dir, i * fov / WIDTH);
		direction = cast_ray(window->player->pos, &dir, &target, window->map);
		draw_vertical_line(window, &target, i + WIDTH / 2, direction);
		i++;
	}	
}

static void	draw_vertical_line(t_window *window, t_vector *target, int i,
				enum e_direction direction)
{
	const double	line_height = HEIGHT * 100 / distance_perpendicular(
			*window->player->pos, *window->player->dir, *target);
	const int		start = max(((HEIGHT - line_height) / 2), 0);
	int				y;
	uint32_t		pix;
	t_vector		tex;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < start)
			mlx_put_pixel(window->img, i, y++, BLACK);
		else if (y > start + line_height)
			mlx_put_pixel(window->img, i, y++, WHITE);
		else
		{
			tex.x = texture_x_value(window->map->all_textures[direction],
					target, window->map, direction);
			tex.y = texture_y_value(window->map->all_textures[direction],
					line_height, y, start);
			pix = get_rgba_from_tex(window->map->all_textures[direction],
					tex.x, tex.y);
			mlx_put_pixel(window->img, i, y++, pix);
		}
	}
}

//make sure this thinking is correct, my thought is you always should hit now
static void	set_target(t_vector *target, t_vector *pos, t_vector *dir, int i)
{
	target->x = pos->x - i * dir->x;
	target->y = pos->y - i * dir->y;
}

static enum e_direction	get_direction(t_vector *dir, char c)
{
	enum e_direction	direction;

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

static int	cast_ray(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	int			i;
	t_vector	temp;
	int			direction;

	temp = (t_vector){pos->x, pos->y, pos->z};
	i = 0;
	direction = north;
	while (on_screen(temp.x, temp.y))
	{
		temp.x = pos->x - i * dir->x;
		if (get_cube_type(&temp, map) == wall)
		{
			direction = get_direction(dir, 'x');
			break ;
		}
		temp.y = pos->y - i * dir->y;
		if (get_cube_type(&temp, map) == wall)
		{
			direction = get_direction(dir, 'y');
			break ;
		}
		i++;
	}
	return (set_target(target, pos, dir, i), direction);
}
