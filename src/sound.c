#include <cub3D.h>

void	play_sound(t_window *window, t_sound_type sound_type)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (sound_type == pistol)
			system("say pew");
		free_everything(window);
		exit(0);
	}
	else
		return ;
}
