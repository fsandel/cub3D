#include <cub3D.h>

void	setup_hud(t_window *window)
{
	window->hud = malloc(sizeof(t_hud) * 1);
	window->hud->fps = malloc(sizeof(t_fps) * 1);
	window->hud->fps->fps_image = NULL;
}

void	fps(void *arg)
{
	t_window	*window;
	char		*fps_char;
	const int	x_position = WIDTH - 50;
	const int	y_position = 20;
	mlx_image_t	*temp_img;

	window = (t_window *)arg;
	window->hud->fps->fps_num = (int)(1 / window->mlx->delta_time);
	fps_char = ft_itoa(window->hud->fps->fps_num);
	temp_img = window->hud->fps->fps_image;
	window->hud->fps->fps_image = mlx_put_string(window->mlx, fps_char,
			x_position, y_position);
	if (temp_img)
		mlx_delete_image(window->mlx, temp_img);
	free(fps_char);
}
