#include <cub3D.h>

static bool	extension_valid(char *filepath);

/*
 * returns a filedescriptor if arg is valid valid path to cub map else -1
 */
int	args_valid(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (-1);
	if (!extension_valid(argv[1]))
	{
		ft_printf("file extension invalid\n");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("not a valid file\n");
		close(fd);
	}
	return (fd);
}

static bool	extension_valid(char *filepath)
{
	int		len;
	char	*extension;

	len = ft_strlen(filepath);
	extension = ft_substr(filepath, len - 4, 4);
	if (ft_strncmp(extension, ".cub", 4))
		return (free(extension), false);
	return (free(extension), true);
}
