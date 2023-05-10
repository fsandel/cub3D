#include <cub3D.h>

static void	set_hp(t_enemy *enemy)
{
	short	hp[8];

	hp[big_hans_blue] = 25;
	hp[big_hans_red] = 25;
	hp[dog] = 5;
	hp[guard] = 10;
	hp[hans] = 20;
	hp[mutant] = 20;
	hp[officer] = 30;
	hp[surgeon] = 30;
	enemy->hp = hp[enemy->type];
}

static void	set_range(t_enemy *enemy)
{
	short	range[8];

	range[big_hans_blue] = 2;
	range[big_hans_red] = 2;
	range[dog] = 1;
	range[guard] = 3;
	range[hans] = 3;
	range[mutant] = 1;
	range[officer] = 3;
	range[surgeon] = 1;
	enemy->range = range[enemy->type];
}

static void	set_speed(t_enemy *enemy)
{
	short	speed[8];

	speed[big_hans_blue] = 1;
	speed[big_hans_red] = 1;
	speed[dog] = 3;
	speed[guard] = 2;
	speed[hans] = 2;
	speed[mutant] = 2;
	speed[officer] = 2;
	speed[surgeon] = 1;
	enemy->speed = speed[enemy->type];
}

static void	set_attack(t_enemy *enemy)
{
	short	attack[8];

	attack[big_hans_blue] = 10;
	attack[big_hans_red] = 10;
	attack[dog] = 10;
	attack[guard] = 10;
	attack[hans] = 10;
	attack[mutant] = 10;
	attack[officer] = 10;
	attack[surgeon] = 10;
	enemy->attack = attack[enemy->type];
}

void	setup_enemy_type_speficic_values(t_enemy *enemy)
{
	set_hp(enemy);
	set_range(enemy);
	set_speed(enemy);
	set_attack(enemy);
}
