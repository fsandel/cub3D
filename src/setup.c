#include <cub3D.h>

static void		implement_loop_hooks(t_window *window);
static t_window	*setup_window_struct(t_map *map);
static void		setup_mouse(t_window *window);
static bool		load_extra_wall_textures(t_window *window);

void			frame_counter_hook(void *arg);
void			start_screen_loop_hook(void *arg);

t_window	*general_setup(t_map *map)
{
	t_window	*window;

	window = setup_window_struct(map);
	if (!window)
		return (ft_lstclear(&map->enemy_list, free), free_map(map), NULL);
	window->player = setup_player(window->map);
	if (!window->player)
		return (ft_lstclear(&map->enemy_list, free), free_map(map),
			free_window(window), NULL);
	window->all_enemies = setup_enemy_struct(window->player, map);
	if (!window->all_enemies)
		return (ft_lstclear(&map->enemy_list, free), free_map(map),
			free_window(window), free_player(window->player), NULL);
	window->hud = setup_hud(window->mlx);
	if (!window->hud)
		return (ft_lstclear(&map->enemy_list, free), free_map(map),
			free_window(window), free_player(window->player),
			free_all_enemies(window->all_enemies), NULL);
	setup_mouse(window);
	implement_loop_hooks(window);
	mlx_key_hook(window->mlx, start_screen_hook, window);
	return (window);
}

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	if (!window)
		return (NULL);
	window->mlx = mlx_init(WIDTH, HEIGHT + HUD_SIZE, "cub3D", 1);
	if (!window->mlx)
		return (free(window), NULL);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT + HUD_SIZE);
	if (!window->img)
		return (free(window), mlx_terminate(window->mlx), NULL);
	if (mlx_image_to_window(window->mlx, window->img, 0, 0) == -1)
		return (free(window), mlx_terminate(window->mlx), NULL);
	mlx_set_instance_depth(window->img->instances, 1);
	window->map = map;
	if (!load_extra_wall_textures(window))
		return (free(window), mlx_terminate(window->mlx), NULL);
	window->frame_count = 0;
	window->redraw = true;
	window->fog = FOG;
	window->state = start_screen;
	return (window);
}

static bool	load_extra_wall_textures(t_window *window)
{
	window->ammo_tex[0] = mlx_load_png("textures/interactable/wolf_ammo.png");
	window->ammo_tex[1] = mlx_load_png("textures/interactable/wolf_empty.png");
	window->health_tex[0]
		= mlx_load_png("textures/interactable/wolf_health.png");
	window->health_tex[1]
		= mlx_load_png("textures/interactable/wolf_empty.png");
	window->exit_tex[0] = mlx_load_png("textures/interactable/wolf_exit.png");
	window->exit_tex[1] = mlx_load_png("textures/interactable/wolf_exit1.png");
	window->destructible_tex = mlx_load_png("textures/wolf_destr_wood.png");
	if (!(window->ammo_tex[0] &&window->ammo_tex[1] && window->health_tex[0]
		&& window->health_tex[1] && window->exit_tex[0] && window->exit_tex[1]
		&& window->destructible_tex))
		{
			ft_mlx_delete_texture(window->ammo_tex[0]);
			ft_mlx_delete_texture(window->ammo_tex[1]);
			ft_mlx_delete_texture(window->health_tex[0]);
			ft_mlx_delete_texture(window->health_tex[1]);
			ft_mlx_delete_texture(window->exit_tex[0]);
			ft_mlx_delete_texture(window->exit_tex[1]);
			ft_mlx_delete_texture(window->destructible_tex);
			return (false);
		}
	return (true);
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
