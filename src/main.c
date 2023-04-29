#include <cub3D.h>

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	window->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	mlx_set_instance_depth(window->img->instances, 1);
	window->map = map;
	window->player = malloc(sizeof(t_player));
	window->player->hp = 100;
	window->player->pos = window->map->start_pos;
	window->player->dir = window->map->start_dir;
	window->redraw = true;
	setup_enemy_struct(window, map);
	window->fog = FOG;
	return (window);
}

static void	player_shoot(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state == dead || window->all_enemies[i]->state == out_of_range)
			i++;
		else if (fabs(window->all_enemies[i]->delta_angle) <= FOV * M_PI / 180.0 / 10.0)
			window->all_enemies[i++]->hitpoints -= 1;
		else
			i++;
	}
}

static	void	muzzle_flair(void *arg)
{
	t_window	*window;
	static int	counter = 0;
	static int	cooldown = 0;

	window = (t_window *)arg;
	if (mlx_is_mouse_down(window->mlx, MLX_MOUSE_BUTTON_LEFT) && cooldown == 0)
	{
		player_shoot(window);
		window->fog += 10;
		cooldown = 10;
		counter = 4;
		window->redraw = true;
	}
	if (counter > 0)
		counter--;
	if (counter == 0)
	{
		window->fog = FOG;
		window->redraw = true;
	}
	if (cooldown > 0)
		cooldown--;
}

static	void	redraw_window(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->redraw == true)
	{
		draw_scene(window);
		window->redraw = false;
	}
}

int	main(int argc, char **argv)
{
	t_window	*window;
	t_map		*map;
	int			fd;

	fd = args_valid(argc, argv);
	map = NULL;
	if (fd != -1)
		map = parse(fd);
	else
		return (EXIT_FAILURE);
	if (!map)
		return (EXIT_FAILURE);
	window = setup_window_struct(map);
	setup_hud(window);
	mlx_loop_hook(window->mlx, player_movement, window);
	mlx_loop_hook(window->mlx, draw_hud, window);
	mlx_key_hook(window->mlx, cub_key_hook, window);
	mlx_loop_hook(window->mlx, redraw_window, window);
	mlx_loop_hook(window->mlx, enemie_handler, window);
	mlx_loop_hook(window->mlx, muzzle_flair, window);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}
