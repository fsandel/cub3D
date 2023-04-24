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
	window->map->door = mlx_load_png("textures/lock.png"); //remember to yeet this line later
	window->map->placeholder = mlx_load_png("textures/placeholder.png"); //remember to yeet this line later
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
	setup_hud(window);
	mlx_loop_hook(window->mlx, escape_handler, window->mlx);
	mlx_loop_hook(window->mlx, player_movement, window);
	mlx_loop_hook(window->mlx, draw_hud, window);
	window->map->cubes[5][24] = door_closed;
	draw_scene(window);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}
