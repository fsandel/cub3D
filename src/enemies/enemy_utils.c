#include <cub3D.h>

void	set_enemy_dir(t_enemy *enemy, t_player *player)
{
	enemy->dir.x = enemy->pos.x - player->pos.x;
	enemy->dir.y = enemy->pos.y - player->pos.y;
	norm(&enemy->dir, 1);
}
