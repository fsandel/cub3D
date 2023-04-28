#include <cub3D.h>

void	set_enemy_dir(t_enemy *enemy, t_player *player)
{
	enemy->dir.x = player->pos->x - enemy->pos.x;
	enemy->dir.y = player->pos->y - enemy->pos.y;
}
