#include <cub3D.h>

bool	args_valid(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		return (false);
	i = 0;
	while (argv[1][i])
	{
		if (ft_isalnum(argv[1][i]) == 1
			|| argv[1][i] == '/' || argv[1][i] == '.')
			i++;
		else
		{
			ft_printf("char: %c is invalid\n", argv[1][i]);
			return (false);
		}
	}
	return (true);
}
