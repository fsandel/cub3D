#include <cub3D.h>

void	rotate_hor_f(t_vector_f *before, t_vector_f *after, double angle);
void	put_square(mlx_image_t *img, t_vector_f *pos, int color);
void	cast_ray(t_vector_f *pos, t_vector_f *dir,
			t_vector_f *target, t_map *map);

void	put_player(t_window *window, int color)
{
	t_vector_f		target;
	t_vector_f		dir;
	double			angle;
	const double	fov = FOV / 40;
	int				i;

	i = -WIDTH / 2;
	put_square(window->img, window->player->pos, color);
	while (i < WIDTH / 2 + 1)
	{
		angle = i * fov / WIDTH;
		rotate_hor_f(window->player->dir, &dir, angle);
		cast_ray(window->player->pos, &dir, &target, window->map);
		put_square(window->img, &target, color);
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

void	turn_player(t_window *window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
	{
		put_player(window, 0x0);
		rotate_hor_f(window->player->dir, window->player->dir, 0.1f);
		put_player(window, 0xFFFFFF);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
	{
		put_player(window, 0x0);
		rotate_hor_f(window->player->dir, window->player->dir, -0.1f);
		put_player(window, 0xFFFFFF);
	}
}

void	player_movement(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
	{
		put_player(window, 0x0);
		window->player->pos->x -= window->player->dir->x;
		window->player->pos->y -= window->player->dir->y;
		put_player(window, 0xFFFFFF);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
	{
		put_player(window, 0x0);
		window->player->pos->x += window->player->dir->x;
		window->player->pos->y += window->player->dir->y;
		put_player(window, 0xFFFFFF);
	}
	turn_player(window);
}
