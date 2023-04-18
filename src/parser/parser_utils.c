#include <cub3D.h>

void	parse_rgb(char *str, int *r, int *g, int *b)
{
	char	*temp;
	char	**str_vals;
	int		i;

	temp = ft_strtrim(str, "FC ");
	str_vals = ft_split(temp, ',');
	i = 0;
	while (i < 3)
	{
		if (i == 0)
			*r = ft_atoi(str_vals[i]);
		else if (i == 1)
			*g = ft_atoi(str_vals[i]);
		else if (i == 2)
			*b = ft_atoi(str_vals[i]);
		i++;
	}
	ft_arr_free(str_vals);
	free(temp);
}
