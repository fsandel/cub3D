#include <cub3D.h>

int	main(int argc, char **argv)
{
	mlx_t	*mlx;
	int		fd;

	fd = args_valid(argc, argv);
	if (fd > 2)
		parse(argv[1]);
	else
		ft_putstr_fd("Error\nArgument invalid\n", STDERR_FILENO);
	mlx = mlx_init(100, 100, "hi philipp", 1);
	if (!mlx)
		ft_printf("MLX_init failed");
	mlx_loop(mlx);
	return (0);
}
