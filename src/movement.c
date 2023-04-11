#include <cub3D.h>

void	rotate_hor_f(t_vector_f *before, t_vector_f *after, double angle);
void	put_square(mlx_image_t *img, t_vector_f *pos, int color);
void	cast_ray(t_vector_f *pos, t_vector_f *dir,
			t_vector_f *target, t_map *map);

void	draw_line(t_window *window, t_vector_f *dir, t_vector_f *target, int i)
{
	const double	lineHeight = HEIGHT * 100 / distancePerp(*window->player->pos, *window->player->dir, *target);
	int				start;
	int				end;
	int				y;

	start = (- lineHeight / 2 + HEIGHT / 2);
	end = (lineHeight / 2 + HEIGHT / 2);
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
	(void)dir;
}

void	put_player(t_window *window)
{
	t_vector_f		target;
	t_vector_f		dir;
	double			angle;
	const double	fov = FOV / 40;
	int				i;

	i = -WIDTH / 2;
	while (i < WIDTH / 2)
	{
		angle = i * fov / WIDTH;
		rotate_hor_f(window->player->dir, &dir, angle);
		cast_ray(window->player->pos, &dir, &target, window->map);
		draw_line(window, &dir, &target, i + WIDTH / 2);
		i++;
	}
}

void	cast_ray(t_vector_f *pos, t_vector_f *dir,
	t_vector_f *target, t_map *map)
{
	int			i;
	t_vector_f	temp;

	temp = (t_vector_f){pos->x, pos->y, pos->z};
	i = 0;
	while (on_screen(temp.x, temp.y) && get_map_char(&temp, map) != '1')
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

void	player_movement(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
	{
		window->player->pos->x -= window->player->dir->x;
		window->player->pos->y -= window->player->dir->y;
		put_player(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
	{
		window->player->pos->x += window->player->dir->x;
		window->player->pos->y += window->player->dir->y;
		put_player(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
	{
		rotate_hor_f(window->player->dir, window->player->dir, 0.1f);
		put_player(window);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
	{
		rotate_hor_f(window->player->dir, window->player->dir, -0.1f);
		put_player(window);
	}
}
