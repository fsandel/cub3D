#include <cub3D.h>

static bool	is_cub_file(char *filepath);

/*
 * returns a filedescriptor if arg is valid valid path to cub map else -1
 */
int	args_valid(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (-1);
	if (!is_cub_file(argv[1]))
	{
		ft_putendl_fd("Error\nFile extension invalid", STDERR_FILENO);
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error\nFile couldn't be opened", STDERR_FILENO);
		close(fd);
	}
	return (fd);
}

/*
 * returns true if the given string ends on .cub
 */
static bool	is_cub_file(char *filepath)
{
	int		len;
	char	*extension;

	len = ft_strlen(filepath);
	extension = ft_substr(filepath, len - 4, 4);
	if (ft_strncmp(extension, ".cub", 4))
		return (free(extension), false);
	return (free(extension), true);
}
