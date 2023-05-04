#include <cub3D.h>

static t_weapon	*setup_weapon(void);

t_player	*setup_player(t_map *map)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	player->hp = STARTING_HP;
	player->ammo = STARTING_AMMO;
	player->pos = map->start_pos;
	player->dir = map->start_dir;
	player->weapon = setup_weapon();
	return (player);
}

static t_weapon	*setup_weapon(void)
{
	t_weapon	*weapon;

	weapon = malloc(sizeof(t_weapon));
	weapon->weapon_type = gun;
	weapon->cooldown = 0;
	weapon->gun_tex[0] = mlx_load_png("textures/gun0.png");
	weapon->gun_tex[1] = NULL;
	weapon->torch_tex[0] = mlx_load_png("textures/torch0.png");
	weapon->torch_tex[1] = mlx_load_png("textures/torch1.png");
	weapon->torch_tex[2] = mlx_load_png("textures/torch2.png");
	weapon->torch_tex[3] = mlx_load_png("textures/torch3.png");
	weapon->torch_tex[4] = mlx_load_png("textures/torch4.png");
	weapon->torch_tex[5] = mlx_load_png("textures/torch5.png");
	weapon->torch_tex[6] = mlx_load_png("textures/torch6.png");
	weapon->torch_tex[7] = mlx_load_png("textures/torch7.png");
	weapon->torch_tex[8] = NULL;
	weapon->muzzle_tex[0] = mlx_load_png("textures/muzzle_flash.png");
	weapon->muzzle_tex[1] = NULL;
	return (weapon);
}
