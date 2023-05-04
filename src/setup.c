#include <cub3D.h>

static void		implement_loop_hooks(t_window *window);
static t_window	*setup_window_struct(t_map *map);
static void		setup_mouse(t_window *window);
void			frame_counter_hook(void *arg);
void			start_screen_loop_hook(void *arg);
static t_weapon	*setup_weapon(void);

t_window	*general_setup(t_map *map)
{
	t_window	*window;

	window = setup_window_struct(map);
	setup_enemy_struct(window, map);
	setup_hud(window);
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
	window->player = malloc(sizeof(t_player));
	window->player->hp = STARTING_HP;
	window->player->ammo = STARTING_AMMO;
	window->player->pos = window->map->start_pos;
	window->player->dir = window->map->start_dir;
	window->player->weapon = setup_weapon();
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

static t_weapon	*setup_weapon(void)
{
	t_weapon	*weapon;

	weapon = malloc(sizeof(t_weapon));
	weapon->weapon_type = gun;
	weapon->gun_tex[0] = mlx_load_png("textures/gun0.png");
	weapon->gun_tex[1] = NULL;
	weapon->torch_tex[0] = mlx_load_png("textures/torch0.png");
	weapon->torch_tex[1] = mlx_load_png("textures/torch1.png");
	weapon->torch_tex[2] = mlx_load_png("textures/torch2.png");
	weapon->torch_tex[3] = mlx_load_png("textures/torch3.png");
	weapon->torch_tex[4] = mlx_load_png("textures/torch4.png");
	weapon->torch_tex[5] = mlx_load_png("textures/torch5.png");
	weapon->torch_tex[6] = mlx_load_png("textures/torch6.png");
	weapon->torch_tex[7] = mlx_load_png("textures/torch7.png");
	weapon->torch_tex[8] = NULL;
	return (weapon);
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
