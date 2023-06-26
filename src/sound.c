#include <cub3D.h>

#ifdef __linux__
# define OS 1
#elif __APPLE__
# define OS 2
#else
# define OS 0
#endif

static char	*get_sound_str_mac(t_sound_type sound_type);
static char	*get_sound_str_linux(t_sound_type sound_type);

void	play_sound(t_sound_type sound_type)
{
	char	*sound_str;
	int		system_error;

	system_error = 0;
	if (OS == 1)
		sound_str = get_sound_str_linux(sound_type);
	else if (OS == 2)
		sound_str = get_sound_str_mac(sound_type);
	else
		sound_str = NULL;
	if (sound_str)
		system_error = system(sound_str);
	if (system_error)
		ft_putendl_fd("Error\nSomething went wrong playing sounds", 2);
	free(sound_str);
}

static char	*get_sound_str_linux(t_sound_type sound_type)
{
	if (sound_type == pistol_fire)
		return (ft_strdup("aplay sounds/pistol_fire.wav&"));
	else if (sound_type == burst_fire)
		return (ft_strdup("aplay sounds/burst_fire.wav&"));
	else if (sound_type == stab_attack)
		return (ft_strdup("aplay sounds/stab_attack.wav&"));
	else if (sound_type == bite_attack)
		return (ft_strdup("aplay sounds/bite_attack.wav&"));
	else if (sound_type == wall_smash)
		return (ft_strdup("aplay sounds/wall_smash.wav&"));
	else if (sound_type == door_sound)
		return (ft_strdup("aplay sounds/door_sound.wav&"));
	else if (sound_type == gun_draw)
		return (ft_strdup("aplay sounds/gun_draw.wav&"));
	else if (sound_type == ammo_pickup)
		return (ft_strdup("aplay sounds/ammo_pickup.wav&"));
	else if (sound_type == health_pickup)
		return (ft_strdup("aplay sounds/health_pickup.wav&"));
	else if (sound_type == start_sound)
		return (ft_strdup("aplay sounds/start_sound.wav&"));
	else if (sound_type == win_sound)
		return (ft_strdup("aplay sounds/win_sound.wav&"));
	else if (sound_type == loss_sound)
		return (ft_strdup("aplay sounds/loss_sound.wav&"));
	return (NULL);
}

static char	*get_sound_str_mac(t_sound_type sound_type)
{
	if (sound_type == pistol_fire)
		return (ft_strdup("afplay sounds/pistol_fire.wav&"));
	else if (sound_type == burst_fire)
		return (ft_strdup("afplay sounds/burst_fire.wav&"));
	else if (sound_type == stab_attack)
		return (ft_strdup("afplay sounds/stab_attack.wav&"));
	else if (sound_type == bite_attack)
		return (ft_strdup("afplay sounds/bite_attack.wav&"));
	else if (sound_type == wall_smash)
		return (ft_strdup("afplay sounds/wall_smash.wav&"));
	else if (sound_type == door_sound)
		return (ft_strdup("afplay sounds/door_sound.wav&"));
	else if (sound_type == gun_draw)
		return (ft_strdup("afplay sounds/gun_draw.wav&"));
	else if (sound_type == ammo_pickup)
		return (ft_strdup("afplay sounds/ammo_pickup.wav&"));
	else if (sound_type == health_pickup)
		return (ft_strdup("afplay sounds/health_pickup.wav&"));
	else if (sound_type == start_sound)
		return (ft_strdup("afplay sounds/start_sound.wav&"));
	else if (sound_type == win_sound)
		return (ft_strdup("afplay sounds/win_sound.wav&"));
	else if (sound_type == loss_sound)
		return (ft_strdup("afplay sounds/loss_sound.wav&"));
	return (NULL);
}
