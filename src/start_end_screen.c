#include <cub3D.h>

static int	get_pixel(int x, int y, mlx_texture_t *tex, mlx_image_t *img)
{
	const int	x_pos = tex->width * x / img->width;
	const int	y_pos = tex->height * y / img->height;
	const int	pos = (y_pos * tex->width + x_pos) * tex->bytes_per_pixel;
	const int	color = get_rgba(tex->pixels[pos],
			tex->pixels[pos + 1],
			tex->pixels[pos + 2],
			tex->pixels[pos + 3]);

	return (color);
}

void	draw_tex_to_screen(mlx_image_t *img, char *texture_string)
{
	unsigned int	i;
	unsigned int	j;
	int				color;
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_string);
	if (!texture)
		return ;
	j = 0;
	while (j < img->height)
	{
		i = 0;
		while (i < img->width)
		{
			color = get_pixel(i, j, texture, img);
			mlx_put_pixel(img, i, j, color);
			i++;
		}
		j++;
	}
	mlx_delete_texture(texture);
}

void	start_screen_hook(mlx_key_data_t keydata, void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(window->mlx);
	else if (keydata.action == MLX_PRESS)
	{
		ft_bzero(window->img->pixels, (HEIGHT + HUD_SIZE) * WIDTH * 4);
		mlx_key_hook(window->mlx, cub_key_hook, window);
		mlx_set_mouse_pos(window->mlx, WIDTH / 2, HEIGHT / 2);
		draw_cross_hair(window);
		window->state = game_screen;
	}
}

void	start_screen_loop_hook(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->state != start_screen)
		return ;
	if (window->frame_count % 24 < 12)
		draw_tex_to_screen(window->img, START_SCREEN1);
	else
		draw_tex_to_screen(window->img, START_SCREEN);
}

void	frame_counter_hook(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->frame_count < INT32_MAX)
		window->frame_count++;
	else
		window->frame_count = 0;
}
