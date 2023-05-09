#include <cub3D.h>

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
	if (map->start_dir)
		free(map->start_dir);
	if (map->start_pos)
		free(map->start_pos);
	free(map->state);
	if (map->door_tex)
		mlx_delete_texture(map->door_tex);
	if (map->cubes)
		free_cubes(map);
}
