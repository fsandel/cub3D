#include <cub3D.h>

bool	is_map_char(char c, int *whitespace);

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

bool	is_map_char(char c, int *whitespace)
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
