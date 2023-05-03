#include <cub3D.h>

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window) * 1);
	window->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	mlx_set_instance_depth(window->img->instances, 1);
	window->map = map;
	window->player = malloc(sizeof(t_player) * 1);
	window->player->pos = window->map->start_pos;
	window->player->dir = window->map->start_dir;
	window->map->placeholder = mlx_load_png("textures/placeholder.png");
	return (window);
}

int	main2(int argc, char **argv)
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
		return (close(fd), EXIT_FAILURE);
	window = setup_window_struct(map);
	setup_hud(window);
	mlx_loop_hook(window->mlx, escape_handler, window->mlx);
	mlx_loop_hook(window->mlx, player_movement, window);
	mlx_loop_hook(window->mlx, draw_hud, window);
	mlx_key_hook(window->mlx, door_handler, window);
	draw_scene(window);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	//system("leaks cub3D");
	return (0);
}
