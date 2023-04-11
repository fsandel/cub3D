#include <cub3D.h>

static bool	extension_valid(char *filepath);

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
	if (!extension_valid(argv[1]))
	{
		ft_printf("file extension invalid\n");
		return (false);
	}
	return (true);
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
