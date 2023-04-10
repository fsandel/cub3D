#include "cub3D.h"

int	parse(int fd)
{
	char	*str;

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
