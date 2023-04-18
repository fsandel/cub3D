#include <cub3D.h>

static bool	is_map_char(char c, int *whitespace);

bool	is_valid_map_str(char *map_str)
{
	int	i;
	int	whitespace;

	i = 0;
	whitespace = 0;
	while (map_str[i])
	{
		if (is_map_char(map_str[i], &whitespace))
			i++;
		else
			return (false);
	}
	if (i == whitespace)
		return (false);
	return (true);
}

bool	is_valid_tex_str(char *tex_str)
{
	if (!ft_strncmp(tex_str, "NO", 2) || !ft_strncmp(tex_str, "SO", 2)
		|| !ft_strncmp(tex_str, "WE", 2) || !ft_strncmp(tex_str, "EA", 2))
		return (true);
	return (false);
}

bool	is_valid_f_c_str(char *f_c_str)
{
	if (f_c_str[0] == 'F' || f_c_str[0] == 'C')
		return (true);
	return (false);
}

static bool	is_map_char(char c, int *whitespace)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	if (c == ' ' || c == '\n')
	{
		*whitespace += 1;
		return (true);
	}
	return (false);
}
