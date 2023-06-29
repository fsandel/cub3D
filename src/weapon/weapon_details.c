#include <cub3D.h>

void	set_weapon_details(t_weapon_type weapon_type, t_vector_int *offset,
		t_vector_int *size)
{
	const int	weapon_size = min(WIDTH, HEIGHT) / 2.5;
	const int	torch_size = min(WIDTH, HEIGHT) / 4;

	if (weapon_type == gun)
	{
		offset->x = WIDTH / 2;
		offset->y = HEIGHT - weapon_size;
		size->x = weapon_size;
		size->y = weapon_size;
	}
	if (weapon_type == torch)
	{
		offset->x = WIDTH / 3 * 2;
		offset->y = HEIGHT - torch_size * 2 / 3;
		size->x = torch_size;
		size->y = torch_size;
	}
}
