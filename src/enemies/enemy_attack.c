#include <cub3D.h>

static void	attack_single_enemy(t_enemy *enemy, t_player *player)
{
	if (enemy->cooldown < 1)
	{
		player->hp -= enemy->attack;
		enemy->cooldown = 30;
	}
	if (enemy->cooldown > 0)
		enemy->cooldown--;
}

void	attack_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state == attacking)
			attack_single_enemy(window->all_enemies[i], window->player);
		i++;
	}
}
