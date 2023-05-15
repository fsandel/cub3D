#include <cub3D.h>

void	set_weapon_details(t_weapon_type weapon_type, t_vector_int *offset,
		t_vector_int *size)
{
	if (weapon_type == gun)
	{
		offset->x = WEAPON_OFFSET_X;
		offset->y = WEAPON_OFFSET_Y;
		size->x = WEAPON_SIZE_X;
		size->y = WEAPON_SIZE_Y;
	}
	if (weapon_type == torch)
	{
		offset->x = TORCH_OFFSET_X;
		offset->y = TORCH_OFFSET_Y;
		size->x = TORCH_SIZE_X;
		size->y = TORCH_SIZE_Y;
	}
}
