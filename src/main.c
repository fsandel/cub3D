#include <cub3D.h>

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window) * 1);
	window->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	window->map = map;
	window->player = malloc(sizeof(t_player) * 1);
	window->player->pos = window->map->start_pos;
	window->player->dir = window->map->start_dir;
	return (window);
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
	window = setup_window_struct(map);
	mlx_loop_hook(window->mlx, escape_handler, window->mlx);
	mlx_loop_hook(window->mlx, player_movement, window);
	draw_scene(window);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}
