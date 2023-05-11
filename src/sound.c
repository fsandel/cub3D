#include <cub3D.h>

static void	get_sound_str(t_sound_type sound_type, char **ret);

void	play_sound(t_window *window, t_sound_type sound_type)
{
	char	*sound_str;

	get_sound_str(sound_type, &sound_str);
	if (sound_str)
		system(sound_str);
	free(sound_str);
	(void)window;
}

static void	get_sound_str(t_sound_type sound_type, char **ret)
{
	if (sound_type == pistol_fire)
		*ret = ft_strdup("afplay sounds/pistol_fire.aiff&");
	else if (sound_type == burst_fire)
		*ret = ft_strdup("afplay sounds/burst_fire.wav&");
	else if (sound_type == stab_attack)
		*ret = ft_strdup("afplay sounds/stab_attack.wav&");
	else if (sound_type == bite_attack)
		*ret = ft_strdup("afplay sounds/bite_attack.wav&");
	else if (sound_type == wall_smash)
		*ret = ft_strdup("afplay sounds/wall_smash.wav&");
	else if (sound_type == door_sound)
		*ret = ft_strdup("afplay sounds/door_sound.wav&");
	else if (sound_type == gun_draw)
		*ret = ft_strdup("afplay sounds/gun_draw.wav&");
	else if (sound_type == ammo_pickup)
		*ret = ft_strdup("afplay sounds/ammo_pickup.aiff&");
	else if (sound_type == health_pickup)
		*ret = ft_strdup("afplay sounds/health_pickup.wav&");
	else if (sound_type == start_sound)
		*ret = ft_strdup("afplay sounds/start_sound.wav&");
	else if (sound_type == win_sound)
		*ret = ft_strdup("afplay sounds/win_sound.mp3&");
	else if (sound_type == loss_sound)
		*ret = ft_strdup("afplay sounds/loss_sound.wav&");
}
