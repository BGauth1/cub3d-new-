/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:32:52 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/31 17:14:01 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	jump(t_camera *c, int speed)
{
	static int	i = -30;
	static int	min = 30 * 30;
	(void) speed;

	if (!c->is_jumping)
	{
		c->is_jumping = 1;
		c->is_landing = 0;
		c->move_speed *= 1.1;
	}
	if (c->is_jumping)
	{
		c->z = 0.4 * (min - (i * i));
		i++;
	}
	if (i == 30)
	{
		c->is_jumping = 0;
		c->is_landing = 1;
		i = -30;
	}
}


void	set_momentum(t_camera *c)
{
	if (!c->is_jumping)
		c->is_landing++;
	else
		c->is_landing = 0;
	if (c->is_landing > 15)
	{
		c->move_speed = P_MV_SPEED;
		c->is_landing = 0;
	}
}