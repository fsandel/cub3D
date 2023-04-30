#include <cub3D.h>

void	redraw_window(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->active == false)
		return ;
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
	window = general_setup(map);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}
