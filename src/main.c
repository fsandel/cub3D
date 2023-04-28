#include <cub3D.h>

static void	setup_enemy_textures(t_enemy **all_enemies);

static void	setup_enemy_struct(t_window *window, t_map *map)
{
	const int			amount = ft_lstsize(map->enemy_list);
	t_enemy				**all_enemies;
	int					i;
	t_list				*head;

	head = map->enemy_list;
	all_enemies = malloc((amount + 1) * sizeof(t_enemy *));
	i = 0;
	while (i < amount)
	{
		all_enemies[i] = malloc(sizeof(t_enemy));
		all_enemies[i]->hitpoints = ENEMIE_HITPOINTS;
		all_enemies[i]->state = out_of_range;
		all_enemies[i]->pos.x = ((t_vector *)(map->enemy_list->content))->x;
		all_enemies[i]->pos.y = ((t_vector *)(map->enemy_list->content))->y;
		map->enemy_list = map->enemy_list->next;
		i++;
	}
	all_enemies[i] = NULL;
	ft_lstclear(&head, free);
	setup_enemy_textures(all_enemies);
	window->all_enemies = all_enemies;
}

static void	setup_enemy_textures(t_enemy **all_enemies)
{
	int	i;
	int	j;

	if (!all_enemies[0])
		return ;
	all_enemies[0]->texture_nb = 2;
	all_enemies[0]->textures[0] = mlx_load_png("textures/rottmonk2.png");
	all_enemies[0]->textures[1] = mlx_load_png("textures/rottmonk2.png");
	i = 0;
	while (all_enemies[i])
	{
		j = 0;
		while (j < all_enemies[0]->texture_nb)
		{
			all_enemies[i]->textures[j] = all_enemies[0]->textures[j];
			j++;
		}
		all_enemies[i++]->texture_nb = all_enemies[0]->texture_nb;
	}
}

static t_window	*setup_window_struct(t_map *map)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	window->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 1);
	window->img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(window->mlx, window->img, 0, 0);
	mlx_set_instance_depth(window->img->instances, 1);
	window->map = map;
	window->player = malloc(sizeof(t_player));
	window->player->pos = window->map->start_pos;
	window->player->dir = window->map->start_dir;
	window->redraw = true;
	setup_enemy_struct(window, map);
	return (window);
}

static	void	redraw_window(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->redraw == true)
	{
		draw_scene(window);
		window->redraw = false;
	}
}

int	main(int argc, char **argv)
{
	t_window	*window;
	t_map		*map;
	int			fd;

	fd = args_valid(argc, argv);
	map = NULL;
	if (fd != -1)
		map = parse(fd);
	else
		return (EXIT_FAILURE);
	if (!map)
		return (EXIT_FAILURE);
	window = setup_window_struct(map);
	setup_hud(window);
	mlx_loop_hook(window->mlx, player_movement, window);
	mlx_loop_hook(window->mlx, draw_hud, window);
	mlx_key_hook(window->mlx, cub_key_hook, window);
	mlx_loop_hook(window->mlx, redraw_window, window);
	mlx_loop_hook(window->mlx, enemie_handler, window);
	mlx_loop(window->mlx);
	free_window_struct(window);
	return (0);
}
