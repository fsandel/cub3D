#include <cub3D.h>

static void	cast_ray(t_vector *pos, t_vector *dir,
				t_vector *target, t_map *map);
static void	draw_vertical_line(t_window *window, t_vector *target, int i);

void	draw_scene(t_window *window)
{
	t_vector		target;
	t_vector		dir;
	double			angle;
	const double	fov = (FOV * M_PI ) / 180;
	int				i;

	i = -WIDTH / 2;
	while (i < WIDTH / 2)
	{
		angle = i * fov / WIDTH;
		rotate_hor_f(window->player->dir, &dir, angle);
		cast_ray(window->player->pos, &dir, &target, window->map);
		draw_vertical_line(window, &target, i + WIDTH / 2);
		i++;
	}
}

static void	draw_vertical_line(t_window *window, t_vector *target, int i)
{
	const double	line_height = HEIGHT * 100 / distance_perpendicular(
			*window->player->pos, *window->player->dir, *target);
	int				start;
	int				end;
	int				y;

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
		else if (y > end)
			mlx_put_pixel(window->img, i, y, RED);
		else
			mlx_put_pixel(window->img, i, y, BLUE);
		y++;
	}
}

static void	cast_ray(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	int			i;
	t_vector	temp;

	temp = (t_vector){pos->x, pos->y, pos->z};
	i = 0;
	while (on_screen(temp.x, temp.y) && get_cube_type(&temp, map) != wall)
	{
		temp.x = pos->x - i * dir->x;
		temp.y = pos->y - i * dir->y;
		i++;
	}
	if (i > 0)
	{
		target->x = pos->x - (i - 1) * dir->x;
		target->y = pos->y - (i - 1) * dir->y;
	}
	else
	{
		target->x = temp.x;
		target->y = temp.y;
	}
}
