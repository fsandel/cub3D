#include <cub3D.h>

static int	cast_ray(t_vector *pos, t_vector *dir,
				t_vector *target, t_map *map);
static void	draw_vertical_line(t_window *window, t_vector *target, int i,
				enum e_direction direction);

uint32_t	get_pixel(mlx_texture_t *tex, int x, int y)
{
	int		i = 0;
	u_int32_t pixel;

	pixel = 0;
	while (i < 4)
	{
		pixel += tex->pixels[(y * tex->width + x) * 4 + i];
		pixel = pixel << 2;
		//pixel *= 256;
		i++;
	}
	return (pixel);
}

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
		//if (i == 0)
		//	printf("x: %f y: %f\n", ft_modf(target.x * window->map->width / WIDTH), ft_modf(target.y * window->map->height / HEIGHT));
		draw_vertical_line(window, &target, i + WIDTH / 2, direction);
		i++;
	}
	int	x = 0;
	int	y = 0;
	uint32_t	color;
	while (x < 50)
	{
		y = 0;
		while (y < 50)
		{
			color = get_pixel(window->map->north, x, y);
			//color = WHITE;
			mlx_put_pixel(window->img, x, y, color);
			y++;
		}
		x++;
	}
	
}

static void	draw_vertical_line(t_window *window, t_vector *target, int i,
				enum e_direction direction)
{
	const double	line_height = HEIGHT * 100 / distance_perpendicular(
			*window->player->pos, *window->player->dir, *target);
	int				start;
	int				end;
	int				y;
	const int		all_colors[] = {BLUE, RED, PINK, YELLOW};
	uint32_t			pix;

	start = (-line_height / 2 + HEIGHT / 2);
	end = (line_height / 2 + HEIGHT / 2);
	if (start < 0)
		start = 0;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT)
	{
		if (y < start)
			mlx_put_pixel(window->img, i, y, BLACK);
		else if (y > start + line_height)
			mlx_put_pixel(window->img, i, y, WHITE);
		else
		{
			//pix = get_pixel_from_texture(target, window->map, line_height, y + start, window->map->north);
			//ft_memcpy(&window->img->pixels[y * WIDTH + i], &pix, 4);
			mlx_put_pixel(window->img, i, y, all_colors[direction]);
		}
		y++;
	}
	(void)pix;
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
			direction = north;
		else
			direction = south;
	}
	else
	{
		if (dir->y > 0)
			direction = west;
		else
			direction = east;
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
