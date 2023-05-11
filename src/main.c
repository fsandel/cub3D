#include <cub3D.h>

int	main2(int argc, char **argv)
{
	t_window	*window;
	t_map		*map;
	int			fd;

	fd = args_valid(argc, argv);
	if (fd != -1)
		map = parse(fd);
	else
		return (EXIT_FAILURE);
	if (!map)
		return (close(fd), EXIT_FAILURE);
	window = general_setup(map);
	if (!window)
		return (ft_putendl_fd("Allocation failed", 2), EXIT_FAILURE);
	mlx_loop(window->mlx);
	free_everything(window);
	return (EXIT_SUCCESS);
}

void	free_everything(t_window *window)
{
	free_all_enemies(window->all_enemies);
	free_map(window->map);
	free_weapon(window->player->weapon);
	free(window->player);
	free(window->hud);
	free_window(window);
}

void	redraw_window(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->state != game_screen)
		return ;
	if (window->redraw == true)
	{
		draw_scene(window);
		window->redraw = false;
	}
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	return (0);
}
