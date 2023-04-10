/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dtest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:17:47 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/10 17:01:17 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	put_square(mlx_image_t *img, int x, int y, int color)
{
	int			i;
	int			j;

	i = -3;
	while (i < 4)
	{
		j = -3;
		while (j < 4)
			mlx_put_pixel(img, x + j++, y + i, color);
		i++;
	}
}



void	player_2d(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	put_square(window->img, window->player->pos->x, window->player->pos->y, 0xFFFFFF);
}

