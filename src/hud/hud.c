#include <cub3D.h>

static void	fps(void *arg);

void	draw_hud(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	fps(window);
	draw_minimap(window);
}

void	setup_hud(t_window *window)
{
	mlx_image_t	*hud_img;

	window->hud = malloc(sizeof(t_hud) * 1);
	window->hud->fps = malloc(sizeof(t_fps) * 1);
	window->hud->minimap = malloc(sizeof(t_minimap) * 1);
	window->hud->fps->fps_image = NULL;
	hud_img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	window->hud->hud_img = hud_img;
	window->hud->minimap->pix_pos_x = 105;
	window->hud->minimap->pix_pos_y = 105;
	window->hud->minimap->zoom = 3;
	window->hud->minimap->radius = 100;
	mlx_image_to_window(window->mlx, window->hud->hud_img, 0, 0);
	mlx_set_instance_depth(window->hud->hud_img->instances, 2);
}

static void	fps(void *arg)
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
