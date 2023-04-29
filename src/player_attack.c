#include <cub3D.h>

static void	player_shoot(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state == dead
			|| window->all_enemies[i]->state == out_of_range)
			i++;
		else if (fabs(window->all_enemies[i]->delta_angle)
			<= FOV * M_PI / 180.0 / 2 / 10)
			window->all_enemies[i++]->hitpoints -= 10;
		else if (fabs(window->all_enemies[i]->delta_angle)
			<= FOV * M_PI / 180.0 / 2 / 5)
			window->all_enemies[i++]->hitpoints -= 4;
		else if (fabs(window->all_enemies[i]->delta_angle)
			<= FOV * M_PI / 180.0 / 2 / 3)
			window->all_enemies[i++]->hitpoints -= 2;
		else
			i++;
	}
}

static	void	muzzle_flair(t_window *window)
{
	static int	counter = 0;
	static int	cooldown = 0;

	if (mlx_is_mouse_down(window->mlx, MLX_MOUSE_BUTTON_LEFT) && cooldown == 0)
	{
		player_shoot(window);
		window->fog += 10;
		cooldown = 10;
		counter = 4;
		window->redraw = true;
	}
	if (counter > 0)
		counter--;
	if (counter == 0)
	{
		window->fog = FOG;
		window->redraw = true;
	}
	if (cooldown > 0)
		cooldown--;
}

void	player_attack(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	muzzle_flair(window);
}
