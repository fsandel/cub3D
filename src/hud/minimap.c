#include <cub3D.h>

static bool	is_on_map(double x, double y, t_map *map)
{
	if (x >= 0 && y >= 0 && x < map->width && y < map->height)
		return (true);
	else
		return (false);
}

static void	put_pixel_minimap(int x_iter, int y_iter, t_window *window,
	int color)
{
	if (window->hud->minimap->pix_pos_x + x_iter < 0)
		return ;
	if (window->hud->minimap->pix_pos_y + y_iter > WIDTH)
		return ;
	if (window->hud->minimap->pix_pos_x + x_iter < 0)
		return ;
	if (window->hud->minimap->pix_pos_x + y_iter > HEIGHT)
		return ;
	mlx_put_pixel(
		window->hud->hud_img,
		window->hud->minimap->pix_pos_x + x_iter,
		window->hud->minimap->pix_pos_y + y_iter,
		color
		);
}

static void	put_minimap_circle(t_window *window, int x, int y)
{
	t_vector		pos;
	const int		size = window->hud->minimap->radius;
	const double	zoom = window->hud->minimap->zoom;

	if (sqrt(x * x + y * y) < size - 2)
	{
		pos.x = window->player->pos->x + x * zoom / size;
		pos.y = window->player->pos->y + y * zoom / size;
		if (is_on_map(pos.x, pos.y, window->map))
		{
			if (get_cube_type(&pos, window->map) == wall)
				put_pixel_minimap(x, y, window, WHITE);
			else
				put_pixel_minimap(x, y, window, window->map->floor_color);
		}
		else
			put_pixel_minimap(x, y, window, window->map->ceiling_color);
		if (sqrt(x * x + y * y) < 4)
			put_pixel_minimap(x, y, window, PINK);
	}
	else if (sqrt(x * x + y * y) < size)
		put_pixel_minimap(x, y, window, BLACK);
}
static void	draw_minimap_ray(t_window *window, t_vector dir)
{
	t_vector	pos;
	const int	size = window->hud->minimap->radius;
	const int	zoom = window->hud->minimap->zoom;
	double		x;
	double		y;

	set_vec(&pos, window->player->pos->x, window->player->pos->y, 0);
	while (get_cube_type(&pos, window->map) != wall)
	{
		x = (pos.x - window->player->pos->x) * size / zoom + window->hud->minimap->pix_pos_x;
		y = (pos.y - window->player->pos->y) * size / zoom + window->hud->minimap->pix_pos_y;
		if (x > 0 && y > 0 && x < WIDTH && y < HEIGHT && sqrt(pow(x - window->hud->minimap->pix_pos_x, 2)+ pow(y - window->hud->minimap->pix_pos_y, 2)) < size) 
		mlx_put_pixel(window->hud->hud_img, x, y, 0x000000ff);
		pos.x -= dir.x * 0.01;
		pos.y -= dir.y * 0.01;
	}
}
static void	draw_minimap_fov(t_window *window)
{
	t_vector	dir;

	set_vec(&dir, window->player->dir->x, window->player->dir->y, 0);
	rotate_hor_f(&dir, &dir, FOV * M_PI / 180 / 2);
	draw_minimap_ray(window, dir);
	set_vec(&dir, window->player->dir->x, window->player->dir->y, 0);
	rotate_hor_f(&dir, &dir, -FOV * M_PI / 180 / 2);
	draw_minimap_ray(window, dir);
}

void	draw_minimap(t_window *window)
{
	const int		size = window->hud->minimap->radius;
	int				x_iter;
	int				y_iter;

	y_iter = -size;
	while (y_iter <= size)
	{
		x_iter = -size;
		while (x_iter <= size)
		{
			put_minimap_circle(window, x_iter, y_iter);
			x_iter++;
		}
		y_iter++;
	}
	draw_minimap_fov(window);
}
