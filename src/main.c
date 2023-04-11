#include <cub3D.h>

static void	escape_handler(void *arg)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window) * 1);
	window->mlx = mlx_init(WIDTH, HEIGHT, "hi philipp", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	window->map = map;
	window->player = malloc(sizeof(t_player) * 1);
	window->player->pos = malloc(sizeof(t_vector_f) * 1);
	window->player->dir = malloc(sizeof(t_vector_f) * 1);
	window->player->pos->x = WIDTH / 2;
	window->player->pos->y = HEIGHT / 2;
	window->player->pos->z = 0;
	window->player->dir->x = 0;
	window->player->dir->y = 10;
	window->player->dir->z = HEIGHT / 2;
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
	put_player(window, 0xFFFFFFF);
	draw_map(window);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}
