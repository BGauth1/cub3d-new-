/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:12:54 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/20 14:02:33 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_pos	fill_pos(int x, int y)
{
	t_pos	res;

	res.x = x;
	res.y = y;
	return (res);
}

t_coord	fill_coord(float x, float y)
{
	t_coord	res;

	res.x = x;
	res.y = y;
	return (res);
}
