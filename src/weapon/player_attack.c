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

static void	player_shoot_wall(t_window *window)
{
	t_vector	temp;

	temp = (t_vector){window->player->pos.x, window->player->pos.y};
	while (get_cube_type(&temp, window->map) < wall)
	{
		temp.x -= window->player->dir.x * 0.01;
		temp.y -= window->player->dir.y * 0.01;
	}
	if (get_cube_type(&temp, window->map) == destructible)
		window->map->cubes[(int)temp.y][(int)temp.x] = walkable;
}

static void	player_shoot_enemies(t_window *window)
{
	int		i;
	bool	hit;

	i = 0;
	hit = false;
	while (window->all_enemies[i])
	{
		hit = hit_enemy(window->all_enemies[i]);
		if (hit)
			break ;
		i++;
	}
	if (!hit)
		player_shoot_wall(window);
}

static	void	player_shoot(t_window *window)
{
	static int	brightness_counter = 0;

	draw_muzzle_flash(window, window->player->weapon->muzzle_tex[0], false);
	if (mlx_is_mouse_down(window->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& window->player->weapon->cooldown == 0
		&& window->player->ammo > 0)
	{
		player_shoot_enemies(window);
		draw_muzzle_flash(window, window->player->weapon->muzzle_tex[0], true);
		window->fog += 10;
		window->player->weapon->cooldown = WEAPON_COOLDOWN;
		brightness_counter = 4;
		window->redraw = true;
		window->player->ammo--;
	}
	if (brightness_counter > 0)
		brightness_counter--;
	if (brightness_counter == 0)
	{
		window->fog = FOG;
		window->redraw = true;
	}
	if (window->player->weapon->cooldown > 0)
		window->player->weapon->cooldown--;
}

void	player_attack(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->state != game_screen)
		return ;
	if (window->player->weapon->weapon_type == gun)
		player_shoot(window);
}
