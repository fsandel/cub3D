/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:31:56 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/11 09:30:16 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	rotate_hor_f(t_vector_f *v, double angle);
void	put_square(mlx_image_t *img, int x, int y, int color);

void	put_player(t_window *window, int color)
{
	put_square(window->img, window->player->pos->x, window->player->pos->y, color);
	put_square(window->img,
			window->player->pos->x - window->player->dir->x * 10,
			window->player->pos->y - window->player->dir->y * 10, color);
}

int	on_screen(int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (1);
	else
		return (0);
}

void	cast_ray(t_window *window, int color)
{
	double	x;
	double	y;
	t_vector_f	v;

	x = window->player->pos->x;
	y = window->player->pos->y;
	while (on_screen(x, y))
	{
		mlx_put_pixel(window->img, x, y, color);
		x -= window->player->dir->x;
		y -= window->player->dir->y;
	}
	v.x = window->player->dir->x;
	v.y = window->player->dir->y;
	v.z = window->player->dir->z;
	x = window->player->pos->x;
	y = window->player->pos->y;
	rotate_hor_f(&v, 0.4f);
	while (on_screen(x, y))
	{
		mlx_put_pixel(window->img, x, y, color);
		x -= v.x;
		y -= v.y;
	}
	v.x = window->player->dir->x;
	v.y = window->player->dir->y;
	v.z = window->player->dir->z;
	x = window->player->pos->x;
	y = window->player->pos->y;
	rotate_hor_f(&v, -0.4f);
	while (on_screen(x, y))
	{
		mlx_put_pixel(window->img, x, y, color);
		x -= v.x;
		y -= v.y;
	}
}



void	player_movement(void *arg)
{
	t_window	*window;
	window = (t_window *)arg;

	if (mlx_is_key_down(window->mlx, MLX_KEY_W))
	{
		put_player(window, 0x0);
		cast_ray(window, 0x0);
		window->player->pos->x -= window->player->dir->x;
		window->player->pos->y -= window->player->dir->y;
		put_player(window, 0xFFFFFF);
		cast_ray(window, 0xFFFFFF);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_S))
	{
		put_player(window, 0x0);
		cast_ray(window, 0x0);
		window->player->pos->x += window->player->dir->x;
		window->player->pos->y += window->player->dir->y;
		put_player(window, 0xFFFFFF);
		cast_ray(window, 0xFFFFFF);
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_D))
	{
		put_player(window, 0x0);
		cast_ray(window, 0x0);
		rotate_hor_f(window->player->dir, 0.1f);
		put_player(window, 0xFFFFFF);
		cast_ray(window, 0xFFFFFF);
		
	}
	if (mlx_is_key_down(window->mlx, MLX_KEY_A))
	{
		put_player(window, 0x0);
		cast_ray(window, 0x0);
		rotate_hor_f(window->player->dir, -0.1f);
		put_player(window, 0xFFFFFF);
		cast_ray(window, 0xFFFFFF);
	}
}
