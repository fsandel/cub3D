#include <cub3D.h>

void	swap_weapon(t_window *window)
{
	if (window->player->weapon->weapon_type != gun)
		play_sound(window, gun_draw);
	window->player->weapon->weapon_type = gun;
}
