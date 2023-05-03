#include <cub3D.h>

static void		implement_loop_hooks(t_window *window);
static t_window	*setup_window_struct(t_map *map);
static void		setup_mouse(t_window *window);
void			frame_counter_hook(void *arg);
void			start_screen_loop_hook(void *arg);
static void		setup_weapon(t_window *window);
static void		draw_cross_hair(t_window *window);

t_window	*general_setup(t_map *map)
{
	t_window	*window;

	window = setup_window_struct(map);
	setup_enemy_struct(window, map);
	setup_hud(window);
	setup_mouse(window);
	implement_loop_hooks(window);
	mlx_key_hook(window->mlx, start_screen_hook, window);
	setup_weapon(window);
	draw_cross_hair(window);
	return (window);
}

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	window->mlx = mlx_init(WIDTH, HEIGHT + HUD_SIZE, "cub3D", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT + HUD_SIZE);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	mlx_set_instance_depth(window->img->instances, 1);
	window->map = map;
	window->player = malloc(sizeof(t_player));
	window->player->hp = STARTING_HP;
	window->player->ammo = STARTING_AMMO;
	window->player->pos = window->map->start_pos;
	window->player->dir = window->map->start_dir;
	window->frame_count = 0;
	window->redraw = true;
	window->fog = FOG;
	window->state = start_screen;
	map->ammo_text[0] = mlx_load_png("textures/shelf_ammo.png");
	map->ammo_text[1] = mlx_load_png("textures/shelf_empty1.png");
	map->health_text[0] = mlx_load_png("textures/shelf_health.png");
	map->health_text[1] = mlx_load_png("textures/shelf_empty3.png");
	map->exit_text[0] = mlx_load_png("textures/exit1.png");
	map->exit_text[1] = mlx_load_png("textures/exit2.png");
	return (window);
}

static int	weapon_get_color(double scale_x, double scale_y, mlx_texture_t *tex)
{
	const int	x_pos = tex->width * scale_x;
	const int	y_pos = tex->width * scale_y;
	const int	pos = (y_pos * tex->width + x_pos) * tex->bytes_per_pixel;
	const int	color = get_rgba(tex->pixels[pos],
			tex->pixels[pos + 1],
			tex->pixels[pos + 2],
			tex->pixels[pos + 3]);

	return (color);
}

static void	setup_weapon(t_window *window)
{
	int				x_iter;
	int				y_iter;
	mlx_texture_t	*tex;
	const int		x_max = 200;
	const int		y_max = 200;
	int				color;
	const int		x_offset = 300;
	const int		y_offset = 300;

	tex = mlx_load_png("textures/gun0.png");
	y_iter = -y_max;
	while (++y_iter < y_max)
	{
		x_iter = -x_max;
		while (++x_iter < x_max)
		{
			color = weapon_get_color(1 - (x_max - x_iter) / 2.0 / x_max , 1 - (y_max - y_iter) / 2.0 / y_max, tex);
			mlx_put_pixel(window->hud->hud_img, x_iter + x_offset, y_iter + y_offset, color);
		}
	}
	mlx_delete_texture(tex);
}

static void	draw_cross_hair(t_window *window)
{
	int			x_iter;
	int			y_iter;
	const int	size = 20;
	const int	width = 2;

	y_iter = -size;
	while (y_iter <= size)
	{
		x_iter = -width;
		while (x_iter <= width)
		{
			mlx_put_pixel(window->hud->hud_img, x_iter + WIDTH / 2, y_iter + HEIGHT / 2, 0x000000ff);
			x_iter++;
		}
		y_iter++;
	}
	y_iter = -width;
	while (y_iter <= width)
	{
		x_iter = -size;
		while (x_iter <= size)
		{
			mlx_put_pixel(window->hud->hud_img, x_iter + WIDTH / 2, y_iter + HEIGHT / 2, 0x000000ff);
			x_iter++;
		}
		y_iter++;
	}
}
static void	setup_mouse(t_window *window)
{
	mlx_set_cursor_mode(window->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(window->mlx, WIDTH / 2, HEIGHT / 2);
}

static void	implement_loop_hooks(t_window *window)
{
	mlx_loop_hook(window->mlx, start_screen_loop_hook, window);
	mlx_loop_hook(window->mlx, player_movement, window);
	mlx_loop_hook(window->mlx, draw_hud, window);
	mlx_loop_hook(window->mlx, redraw_window, window);
	mlx_loop_hook(window->mlx, enemie_handler, window);
	mlx_loop_hook(window->mlx, player_attack, window);
	mlx_loop_hook(window->mlx, mouse_movement, window);
	mlx_loop_hook(window->mlx, check_dead, window);
	mlx_loop_hook(window->mlx, frame_counter_hook, window);
}
