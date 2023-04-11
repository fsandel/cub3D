#include "cub3D.h"

int	parse(char *path)
{
	char	*str;
	int		fd;

	fd = open(path, O_RDONLY);
	str = get_next_line(fd);
	while (str != NULL)
	{
		if (str != NULL)
		{
			ft_printf("%s", str);
			free(str);
		}
		str = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}
