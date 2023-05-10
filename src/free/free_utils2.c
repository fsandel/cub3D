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
	ft_mlx_delete_texture(map->textures[north]);
	ft_mlx_delete_texture(map->textures[east]);
	ft_mlx_delete_texture(map->textures[south]);
	ft_mlx_delete_texture(map->textures[west]);
	free(map->state);
	ft_mlx_delete_texture(map->door_tex);
	if (map->cubes)
		free_cubes(map);
	free(map);
}

void	ft_mlx_delete_texture(mlx_texture_t *texture)
{
	if (!texture)
		return ;
	mlx_delete_texture(texture);
}
