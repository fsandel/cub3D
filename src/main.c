/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:44:07 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/10 18:19:34 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	player_2d(void *arg);
void	player_movement(void *arg);
void	put_square(mlx_image_t *img, int x, int y, int color);

void	draw_map(t_window *window)
{
	int	x;
	int	y;
	int	width;
	int	height;

	int	i = 0;
	while (window->map[i])
		ft_putendl_fd(window->map[i++], 1);
	width = ft_strlen(window->map[0]);
	height = ft_arr_size(window->map);
	x = 0;
	
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (window->map[x * width / WIDTH][y * height / HEIGHT])
				mlx_put_pixel(window->img, x, y, 0xff0000ff);
			y++;
		}
		x++;
	}
}

void	escape_handler(void *arg)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

t_window	*setup_window_struct(void)
{
	t_window	*window;
	int			fd;

	window = malloc(sizeof(t_window) * 1);
	window->mlx = mlx_init(WIDTH, HEIGHT, "hi philipp", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	fd = open("testmap.txt", O_RDONLY);
	window->map = ft_read_file(fd);
	window->player = malloc(sizeof(t_player) * 1);
	window->player->pos = malloc(sizeof(t_v_i) * 1);
	window->player->dir = malloc(sizeof(t_v_f) * 1);
	window->player->pos->x = WIDTH / 2;
	window->player->pos->y = HEIGHT / 2;
	window->player->pos->z = 0;
	window->player->dir->x = 0;
	window->player->dir->y = 10;
	window->player->dir->z = HEIGHT / 2;
	close(fd);
	return (window);
}

void	free_window_struct(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	mlx_terminate(window->mlx);
	ft_arr_free(window->map);
	free(window->player->dir);
	free(window->player->pos);
	free(window->player);
	free(window);
}

int	main(void)
{
	t_window	*window;

	window = setup_window_struct();
	mlx_loop_hook(window->mlx, escape_handler, window->mlx);
	//mlx_loop_hook(window->mlx, player_2d, window);
	mlx_loop_hook(window->mlx, player_movement, window);
	put_square(window->img, window->player->pos->x, window->player->pos->y, 0xFFFFFFF);
	//draw_map(window);
	mlx_loop(window->mlx);
	ft_printf("am after loop\n");
	free_window_struct(window);
	return (0);
}
