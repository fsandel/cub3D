#include <cub3D.h>

void	player_movement(void *arg);
void	put_player(t_window *window);

void	escape_handler(void *arg)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

t_window	*setup_window_struct(void)
{
	t_window	*window;
	int			fd;

	window = malloc(sizeof(t_window) * 1);
	window->mlx = mlx_init(WIDTH, HEIGHT, "hi philipp", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	fd = open("testmap.txt", O_RDONLY);
	window->map = malloc(sizeof(t_map) * 1);
	window->map->array = ft_read_file(fd);
	window->map->heigth = ft_arr_size(window->map->array);
	window->map->width = ft_strlen(window->map->array[0]);
	window->player = malloc(sizeof(t_player) * 1);
	window->player->pos = malloc(sizeof(t_vector_f) * 1);
	window->player->dir = malloc(sizeof(t_vector_f) * 1);
	window->player->pos->x = WIDTH / 2;
	window->player->pos->y = HEIGHT / 2;
	window->player->pos->z = 0;
	window->player->dir->x = 0;
	window->player->dir->y = 10;
	window->player->dir->z = HEIGHT / 2;
	close(fd);
	return (window);
}

void	free_window_struct(t_window *window)
{
	mlx_delete_image(window->mlx, window->img);
	mlx_terminate(window->mlx);
	ft_arr_free(window->map->array);
	free(window->player->dir);
	free(window->player->pos);
	free(window->player);
	free(window->map);
	free(window);
}

int	main(void)
{
	t_window	*window;

	window = setup_window_struct();
	mlx_loop_hook(window->mlx, escape_handler, window->mlx);
	mlx_loop_hook(window->mlx, player_movement, window);
	put_player(window);
	mlx_loop(window->mlx);
	ft_printf("am after loop\n");
	free_window_struct(window);
	return (0);
}
