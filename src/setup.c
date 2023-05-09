#include <cub3D.h>

static void		implement_loop_hooks(t_window *window);
static t_window	*setup_window_struct(t_map *map);
static void		setup_mouse(t_window *window);
static t_window	*load_extra_wall_textures(t_window *window);

void			frame_counter_hook(void *arg);
void			start_screen_loop_hook(void *arg);

t_window	*general_setup(t_map *map)
{
	t_window	*window;

	window = setup_window_struct(map);
	window->player = setup_player(window->map);
	window->all_enemies = setup_enemy_struct(window->player, map);
	window->hud = setup_hud(window->mlx);
	setup_mouse(window);
	implement_loop_hooks(window);
	mlx_key_hook(window->mlx, start_screen_hook, window);
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
	window = load_extra_wall_textures(window);
	window->frame_count = 0;
	window->redraw = true;
	window->fog = FOG;
	window->state = start_screen;
	return (window);
}

static t_window	*load_extra_wall_textures(t_window *window)
{
	window->ammo_tex[0] = mlx_load_png("textures/interactable/shelf_ammo.png");
	window->ammo_tex[1]
		= mlx_load_png("textures/interactable/shelf_empty1.png");
	window->health_tex[0]
		= mlx_load_png("textures/interactable/shelf_health.png");
	window->health_tex[1]
		= mlx_load_png("textures/interactable/shelf_empty3.png");
	window->exit_tex[0] = mlx_load_png("textures/interactable/exit1.png");
	window->exit_tex[1] = mlx_load_png("textures/interactable/exit2.png");
	window->destructible_tex = mlx_load_png("textures/cracked_wall.png");
	return (window);
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
	mlx_loop_hook(window->mlx, mouse_movement, window);
	mlx_loop_hook(window->mlx, draw_weapon_loop_hook, window);
	mlx_loop_hook(window->mlx, player_attack, window);
	mlx_loop_hook(window->mlx, check_dead, window);
	mlx_loop_hook(window->mlx, frame_counter_hook, window);
}
