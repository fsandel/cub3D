#include <cub3D.h>

static void	fps(t_window *window);
static void	hp(t_window *window);
static void	ammo(t_window *window);

void	draw_hud(void *arg)
{
	t_window	*window;
	static int	delay = 0;

	window = (t_window *)arg;
	if (window->state != game_screen)
		return ;
	draw_minimap(window);
	delay++;
	if (delay == 5)
	{
		delay = 0;
		return ;
	}
	hp(window);
	fps(window);
	ammo(window);
}

t_hud	*setup_hud(mlx_t *mlx)
{
	mlx_image_t	*hud_img;
	t_hud		*hud;

	hud = malloc(sizeof(t_hud));
	hud_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	hud->hud_img = hud_img;
	hud->minimap_pos_x = 105;
	hud->minimap_pos_y = 105;
	hud->minimap_zoom = 5;
	hud->minimap_radius = 100;
	mlx_image_to_window(mlx, hud->hud_img, 0, 0);
	mlx_set_instance_depth(hud->hud_img->instances, 2);
	return (hud);
}

static void	fps(t_window *window)
{
	char				*fps_char;
	char				*fps_char_joined;
	mlx_image_t			*temp_img;
	static mlx_image_t	*fps_img = NULL;
	static int			draw_order = 0;

	draw_order = (draw_order + 1) % 3;
	if (draw_order != 0)
		return ;
	fps_char = ft_itoa(1 / window->mlx->delta_time);
	fps_char_joined = ft_strjoin("FPS: ", fps_char);
	temp_img = fps_img;
	fps_img = mlx_put_string(window->mlx, fps_char_joined,
			WIDTH - 100, HEIGHT + 10);
	mlx_set_instance_depth(fps_img->instances, 3);
	if (temp_img)
		mlx_delete_image(window->mlx, temp_img);
	free(fps_char);
	free(fps_char_joined);
}

static void	hp(t_window *window)
{
	char				*hp_char;
	char				*hp_char_joined;
	mlx_image_t			*temp_img;
	static mlx_image_t	*hp_img = NULL;
	static int			draw_order = 0;

	draw_order = (draw_order + 1) % 3;
	if (draw_order != 1)
		return ;
	hp_char = ft_itoa(window->player->hp);
	hp_char_joined = ft_strjoin("HP: ", hp_char);
	temp_img = hp_img;
	hp_img = mlx_put_string(window->mlx, hp_char_joined,
			WIDTH / 2, HEIGHT + 10);
	mlx_set_instance_depth(hp_img->instances, 3);
	if (temp_img)
		mlx_delete_image(window->mlx, temp_img);
	free(hp_char);
	free(hp_char_joined);
}

static void	ammo(t_window *window)
{
	char				*ammo_char;
	char				*ammo_char_joined;
	mlx_image_t			*temp_img;
	static mlx_image_t	*ammo_img = NULL;
	static int			draw_order = 0;

	draw_order = (draw_order + 1) % 3;
	if (draw_order != 2)
		return ;
	ammo_char = ft_itoa(window->player->ammo);
	ammo_char_joined = ft_strjoin("AMMO: ", ammo_char);
	temp_img = ammo_img;
	ammo_img = mlx_put_string(window->mlx, ammo_char_joined,
			10, HEIGHT + 10);
	mlx_set_instance_depth(ammo_img->instances, 3);
	if (temp_img)
		mlx_delete_image(window->mlx, temp_img);
	free(ammo_char);
	free(ammo_char_joined);
}
