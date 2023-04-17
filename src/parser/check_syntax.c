#include <cub3D.h>

bool	is_map_char(char c);

bool	is_valid_map_str(char *map_str)
{
	int	i;

	i = 0;
	while (map_str[i])
	{
		if (!is_map_char(map_str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == ' ' || c == '\n')
		return (true);
	return (false);
}
