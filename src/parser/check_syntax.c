#include <cub3D.h>

static bool	is_map_char(char c);
static bool	is_valid_color_char(char c);

bool	is_valid_map_str(char *map_str)
{
	int	i;
	int	whitespace;

	i = 0;
	whitespace = 0;
	while (map_str[i])
	{
		if ((map_str[i] == ' ' || map_str[i] == '\n')
			&& is_map_char(map_str[i]))
		{
			whitespace++;
			i++;
		}
		else if (is_map_char(map_str[i]))
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
	bool	res;

	res = false;
	if (!ft_strncmp(tex_str, "NO", 2) || !ft_strncmp(tex_str, "SO", 2)
		|| !ft_strncmp(tex_str, "WE", 2) || !ft_strncmp(tex_str, "EA", 2)
		|| !ft_strncmp(tex_str, "DO", 2))
		res = true;
	if (tex_str[2] != ' ')
		res = false;
	return (res);
}

bool	is_valid_f_c_str(char *f_c_str)
{
	bool	res;
	int		i;
	int		comma_count;

	res = false;
	comma_count = 0;
	if (f_c_str[0] == 'F' || f_c_str[0] == 'C')
		res = true;
	i = 2;
	while (i < (int) ft_strlen(&f_c_str[1]))
	{
		if (!is_valid_color_char(f_c_str[i]))
			return (false);
		if (f_c_str[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		return (false);
	return (res);
}

static bool	is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W'
		|| c == 'D' || c == 'e' || c == 'a' || c == 'h' || c == 'x')
		return (true);
	if (c == ' ' || c == '\n')
		return (true);
	return (false);
}

static bool	is_valid_color_char(char c)
{
	if (ft_isdigit(c) || c == ',')
		return (true);
	else
		return (false);
}
