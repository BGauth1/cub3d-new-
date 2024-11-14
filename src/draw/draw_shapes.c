/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:28:24 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/20 16:28:48 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_line(mlx_image_t *data, t_coord begin, t_coord end, int color)
{
	float	diffx;
	float	diffy;
	float	max_diff;
	int		i;
	t_coord	incr;

	i = -1;
	if (begin.x > end.x)
	{
		ft_fswap(&begin.x, &end.x);
		ft_fswap(&begin.y, &end.y);
	}
	diffx = end.x - begin.x;
	diffy = end.y - begin.y;
	if (ft_abs(diffx) > ft_abs(diffy))
		max_diff = ft_abs(diffx);
	else
		max_diff = ft_abs(diffy);
	incr = fill_coord(diffx / max_diff, diffy / max_diff);
	while (++i < max_diff)
	{
		mlx_put_pixel(data, begin.x, begin.y, color);
		begin.x += incr.x;
		begin.y += incr.y;
	}
}

void	draw_rectangle(mlx_image_t *data, t_pos begin, t_pos end, int color)
{
	int	tmp;

	tmp = begin.x;
	while (begin.y <= end.y)
	{
		while (begin.x <= end.x)
			mlx_put_pixel(data, begin.x++, begin.y, color);
		begin.x = tmp;
		begin.y++;
	}
}
