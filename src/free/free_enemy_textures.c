#include <cub3D.h>

void	free_texture_array(int first_max, int second_max,
			mlx_texture_t *array[first_max][second_max])
{
	int	first_iter;
	int	second_iter;

	first_iter = 0;
	while (first_iter < first_max)
	{
		second_iter = 0;
		while (second_iter < second_max)
		{
			ft_mlx_delete_texture(array[first_iter][second_iter]);
			second_iter++;
		}
		first_iter++;
	}
}
