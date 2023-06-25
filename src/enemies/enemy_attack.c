#include <cub3D.h>

static void	attack_single_enemy(t_enemy *enemy, t_player *player)
{
	if (enemy->cooldown < 1)
	{
		player->hp -= enemy->attack;
		enemy->cooldown = 30;
		if (enemy->type == big_hans_blue || enemy->type == big_hans_red)
			play_sound(burst_fire);
		else if (enemy->type == mutant || enemy->type == surgeon)
			play_sound(stab_attack);
		else if (enemy->type == dog)
			play_sound(bite_attack);
		else
			play_sound(pistol_fire);
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
