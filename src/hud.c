#include <cub3D.h>

void	setup_hud(t_window *window)
{
	window->hud = malloc(sizeof(t_hud) * 1);
	window->hud->fps = malloc(sizeof(t_fps) * 1)
}

void	fps(void *arg)
{
	t_window			*window;
	static mlx_image_t	*fps_img = NULL;
	char				*fps_char;

	window = (t_window *)arg;
	window->
	fps_char = ft_itoa((int)(1 / window->mlx->delta_time));
	if (fps_img)
		mlx_delete_image(window->mlx, fps_img);
	fps_img = mlx_put_string(window->mlx, fps_char, WIDTH - 100, 50);
}