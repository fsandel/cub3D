#include <cub3D.h>

static void		setup_start_screen(t_window *window);
static void		implement_loop_hooks(t_window *window);
static t_window	*setup_window_struct(t_map *map);
static void		setup_mouse(t_window *window);

t_window	*general_setup(t_map *map)
{
	t_window	*window;

	window = setup_window_struct(map);
	setup_enemy_struct(window, map);
	setup_hud(window);
	setup_mouse(window);
	setup_start_screen(window);
	implement_loop_hooks(window);
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
	window->redraw = true;
	window->fog = FOG;
	window->active = false;
	return (window);
}

static void	setup_start_screen(t_window *window)
{
	draw_tex_to_screen(window->img, START_SCREEN);
	mlx_key_hook(window->mlx, start_screen_hook, window);
}

static void	setup_mouse(t_window *window)
{
	mlx_set_cursor_mode(window->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(window->mlx, WIDTH / 2, HEIGHT / 2);
}

static void	implement_loop_hooks(t_window *window)
{
	mlx_loop_hook(window->mlx, player_movement, window);
	mlx_loop_hook(window->mlx, draw_hud, window);
	mlx_loop_hook(window->mlx, redraw_window, window);
	mlx_loop_hook(window->mlx, enemie_handler, window);
	mlx_loop_hook(window->mlx, player_attack, window);
	mlx_loop_hook(window->mlx, mouse_movement, window);
	mlx_loop_hook(window->mlx, check_dead, window);
}
