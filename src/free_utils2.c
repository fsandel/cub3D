#include <cub3D.h>

void	free_map(t_map *map)
{
	if (map->textures[north])
		mlx_delete_texture(map->textures[north]);
	if (map->textures[east])
		mlx_delete_texture(map->textures[east]);
	if (map->textures[south])
		mlx_delete_texture(map->textures[south]);
	if (map->textures[west])
		mlx_delete_texture(map->textures[west]);
	if (map->ammo_text[0])
		mlx_delete_texture(map->ammo_text[0]);
	if (map->ammo_text[1])
		mlx_delete_texture(map->ammo_text[1]);
	if (map->exit_text[0])
		mlx_delete_texture(map->exit_text[0]);
	if (map->exit_text[1])
		mlx_delete_texture(map->exit_text[1]);
	if (map->start_dir)
		free(map->start_dir);
	if (map->start_pos)
		free(map->start_pos);
	free(map->state);
	if (map->door)
		mlx_delete_texture(map->door);
	if (map->cubes)
		free_cubes(map);
}
