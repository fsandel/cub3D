#include <cub3D.h>

static bool	hit_enemy(t_enemy *enemy)
{
	if (enemy->state == dead || enemy->state == out_of_range)
		return (false);
	else if (fabs(enemy->delta_angle) <= FOV * M_PI / 180.0 / 2.0 / 10.0)
		return (enemy->hitpoints -= 10, true);
	else if (fabs(enemy->delta_angle) <= FOV * M_PI / 180.0 / 2.0 / 5.0)
		return (enemy->hitpoints -= 4, true);
	else if (fabs(enemy->delta_angle) <= FOV * M_PI / 180.0 / 2.0 / 3.0)
		return (enemy->hitpoints -= 2, true);
	else
		return (false);
}

static void	player_shoot(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (hit_enemy(window->all_enemies[i]))
			break ;
		i++;
	}
}

static	void	muzzle_flair(t_window *window)
{
	static int	counter = 0;
	static int	cooldown = 0;

	if (mlx_is_mouse_down(window->mlx, MLX_MOUSE_BUTTON_LEFT) && cooldown == 0
		&& window->player->ammo > 0)
	{
		player_shoot(window);
		window->fog += 10;
		cooldown = 10;
		counter = 4;
		window->redraw = true;
		window->player->ammo--;
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
