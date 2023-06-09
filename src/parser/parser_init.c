#include <cub3D.h>

/*
 * inits the map struct
 */
static t_parser_state	*init_state(void)
{
	t_parser_state	*state;

	state = malloc(sizeof(t_parser_state));
	if (!state)
		return (NULL);
	state->map_parsed = false;
	state->f_parsed = false;
	state->c_parsed = false;
	state->contains_door = false;
	state->error_type = no_error;
	return (state);
}

t_map	*init_map(void)
{
	t_map			*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->textures[0] = NULL;
	map->textures[1] = NULL;
	map->textures[2] = NULL;
	map->textures[3] = NULL;
	map->enemy_list = NULL;
	map->width = 0;
	map->height = 0;
	map->door_tex = NULL;
	map->enemy_list = NULL;
	map->has_spawn = false;
	map->floor_color = get_rgba(0, 0, 0, 0);
	map->ceiling_color = get_rgba(0, 0, 0, 0);
	map->state = init_state();
	if (!map->state)
		return (NULL);
	return (map);
}
