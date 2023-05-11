#include <cub3D.h>

// Read-Errors
#define OPT_UNKNWON "Found unexpected option"
#define NO_MAP "File doesn't contain valid map"
#define NO_OPTS "File has no options"
#define MAP_NOT_LAST "No options specified before map"
#define MULTIPLE_MAPS "File contains multiple maps"
// Parse-Errors
#define INVALID_TEXTURE "File contains invalid texture"
#define INVALID_COLOR "Options contain invalid color"
#define TOO_MANY_TEXTURES "File contains too many textures"
#define TOO_MANY_SPAWNS "File contains too many spawn positions"
#define TOO_MANY_COLORS "File contains too many color options"
// Validation-Errors
#define MISSING_OPTION "File misses a mandatory option"
#define INVALID_MAP "Map is invalid - not playable"

static void	print_error(enum e_parser_error err);

void	parser_error(t_file_content *file_content, t_map *map)
{
	print_error(map->state->error_type);
	if (file_content)
		free_filecontent(file_content);
	if (map)
	{
		ft_lstclear(&map->enemy_list, &free);
		free_map(map);
	}
}

static void	print_error(enum e_parser_error err)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (err == opt_unknown)
		ft_putendl_fd(OPT_UNKNWON, STDERR_FILENO);
	else if (err == no_map)
		ft_putendl_fd(NO_MAP, STDERR_FILENO);
	else if (err == multiple_maps)
		ft_putendl_fd(MULTIPLE_MAPS, STDERR_FILENO);
	else if (err == map_not_last)
		ft_putendl_fd(MAP_NOT_LAST, STDERR_FILENO);
	else if (err == no_opts)
		ft_putendl_fd(NO_OPTS, STDERR_FILENO);
	else if (err == invalid_texture)
		ft_putendl_fd(INVALID_TEXTURE, STDERR_FILENO);
	else if (err == invalid_color)
		ft_putendl_fd(INVALID_COLOR, STDERR_FILENO);
	else if (err == too_many_textures)
		ft_putendl_fd(TOO_MANY_TEXTURES, STDERR_FILENO);
	else if (err == too_many_spawns)
		ft_putendl_fd(TOO_MANY_SPAWNS, STDERR_FILENO);
	else if (err == too_many_colors)
		ft_putendl_fd(TOO_MANY_COLORS, STDERR_FILENO);
	else if (err == missing_option)
		ft_putendl_fd(MISSING_OPTION, STDERR_FILENO);
	else if (err == invalid_map)
		ft_putendl_fd(INVALID_MAP, STDERR_FILENO);
}
