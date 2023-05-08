#include <cub3D.h>

static void	free_all_enemies(t_window *window)
{
	int	i;
	int	j;

	j = 0;
	if (window->all_enemies[0])
	{
		while (j < window->all_enemies[0]->walking_texture_nb)
		{
			mlx_delete_texture(window->all_enemies[0]->attacking_textures[j]);
			mlx_delete_texture(window->all_enemies[0]->walking_textures[j++]);
		}
		mlx_delete_texture(window->all_enemies[0]->dead_textures[0]);
	}
	i = 0;
	while (window->all_enemies[i])
		free(window->all_enemies[i++]);
	free(window->all_enemies);
}

void	free_cubes(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height && map->cubes[i])
	{
		free(map->cubes[i]);
		i++;
	}
	free(map->cubes);
}

void	free_filecontent(t_file_content *file_content)
{
	if (file_content)
	{
		if (file_content->map_lines)
			ft_lstclear(&file_content->map_lines, &free);
		if (file_content->option_lines)
			ft_lstclear(&file_content->option_lines, &free);
		free(file_content);
	}
}

static void	free_hud(t_window *window)
{
	free(window->hud->fps);
	free(window->hud->minimap);
	free(window->hud);
}

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
	// TODO: this freeing stuff here leads to segfaults in some cases
	//if (map->health_text[0])
		//mlx_delete_texture(map->health_text[0]);
	//if (map->health_text[1])
		//mlx_delete_texture(map->health_text[1]);
	if (map->exit_text[0])
		mlx_delete_texture(map->exit_text[0]);
	if (map->exit_text[1])
		mlx_delete_texture(map->exit_text[1]);
	if (map->start_dir)
		free(map->start_dir);
	if (map->start_pos)
		free(map->start_pos);
	if (map->state)
		free(map->state);
	if (map->door)
		mlx_delete_texture(map->door);
	if (map->cubes)
		free_cubes(map);
}

void	free_window_struct(t_window *window)
{
	free_all_enemies(window);
	mlx_delete_image(window->mlx, window->img);
	mlx_terminate(window->mlx);
	free_hud(window);
	free(window->player);
	free_map(window->map);
	free(window->map);
	free(window);
}
