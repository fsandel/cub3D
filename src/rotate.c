/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:10:07 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/11 09:29:21 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	norm(t_vector_f *v, double future_length)
{
	double	length;

	length = sqrt((v->x * v->x) + (v->y * v->y));
	v->x = v->x / length * future_length;
	v->y = v->y / length * future_length;
}

void	rotate_hor_f(t_vector_f *v, double angle)
{
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = v->x * sin(angle) + v->y * cos(angle);
	norm(v, 10);
}
