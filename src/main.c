/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 09:44:07 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/10 20:25:04 by pschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	main(void)
{
	mlx_t	*mlx;
	int		fd;

	fd = open("maps/test.cub", O_RDONLY);
	parse(fd);
	mlx = mlx_init(100, 100, "hi philipp", 1);
	if (!mlx)
		ft_printf("MLX_init failed");
	mlx_loop(mlx);
	return (0);
}
