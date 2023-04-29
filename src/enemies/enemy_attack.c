#include <cub3D.h>

static void	attack_single_enemy(t_window *window)
{
	static int	cooldown = 0;

	if (cooldown < 1)
	{
		window->player->hp -= 10;
		cooldown = 30;
		printf("player hp: %d\n", window->player->hp);
	}
	cooldown--;
}

void	attack_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state == attacking)
			attack_single_enemy(window);
		i++;
	}
}
