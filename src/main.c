#include <cub3D.h>

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
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	main2(argc, argv);
	system("leaks cub3D");
	return (0);
}
