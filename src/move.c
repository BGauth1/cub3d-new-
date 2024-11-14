/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:59:42 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/31 17:14:01 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	hit_wall(float x, float y, char **map)
{
	return (map[(int)(y - P_HITBOX)][(int)(x - P_HITBOX)] == '1'
			|| map[(int)(y + P_HITBOX)][(int)(x + P_HITBOX)] == '1'
			|| map[(int)(y + P_HITBOX)][(int)(x - P_HITBOX)] == '1'
			|| map[(int)(y - P_HITBOX)][(int)(x + P_HITBOX)] == '1');
}

void	move_left(t_camera *c, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(c->coord.x + c->dir.y * c->move_speed, c->coord.y, map))
			c->coord.x += c->dir.y * c->move_speed;
		if (!hit_wall(c->coord.x, c->coord.y - c->dir.x * c->move_speed, map))
			c->coord.y -= c->dir.x * c->move_speed;
	}
}

void	move_right(t_camera *c, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(c->coord.x - c->dir.y * c->move_speed, c->coord.y, map))
			c->coord.x -= c->dir.y * c->move_speed;
		if (!hit_wall(c->coord.x, c->coord.y + c->dir.x * c->move_speed, map))
			c->coord.y += c->dir.x * c->move_speed;
	}
}

void	move_up(t_camera *c, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(c->coord.x + c->dir.x * c->move_speed, c->coord.y, map))
			c->coord.x += c->dir.x * c->move_speed;
		if (!hit_wall(c->coord.x, c->coord.y + c->dir.y * c->move_speed, map))
			c->coord.y += c->dir.y * c->move_speed;
	}
}

void	move_down(t_camera *c, char **map)
{
	int	i;

	i = 0;
	while (++i != 5)
	{
		if (!hit_wall(c->coord.x - c->dir.x * c->move_speed, c->coord.y, map))
			c->coord.x -= c->dir.x * c->move_speed;
		if (!hit_wall(c->coord.x, c->coord.y - c->dir.y * c->move_speed, map))
			c->coord.y -= c->dir.y * c->move_speed;
	}
}
