/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:29 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/31 17:16:34 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_keypress(t_cub *cub)
{
	cub->key.m = 0;
}

void	da_key_hook(mlx_key_data_t keydata, void *thing)
{
	t_cub	*cub;

	cub = thing;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		cub->key.m = (cub->key.m != 1);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
		cub->camera.is_jumping = 1;
}

void	turn_left_right(t_camera *c, float speed)
{
	float	olddirx;
	float	oldplanex;

	olddirx = c->dir.x;
	c->dir.x = c->dir.x * cos(speed) - c->dir.y * sin(speed);
	c->dir.y = olddirx * sin(speed) + c->dir.y * cos(speed);
	oldplanex = c->plane.x;
	c->plane.x = c->plane.x * cos(speed) - c->plane.y * sin(speed);
	c->plane.y = oldplanex * sin(speed) + c->plane.y * cos(speed);
}

void	look_up_down(t_camera *c, int speed)
{
	c->up_down += speed;
	if (c->up_down > 1000)
		c->up_down = 1000;
	if (c->up_down < -1000)
		c->up_down = -1000;
}

void	mouse_support(mlx_t *mlx, t_camera *c)
{
	t_pos	pos;
	t_pos	diff;

	mlx_get_mouse_pos(mlx, &pos.x, &pos.y);
	diff = fill_pos(WIN_WIDTH / 2 - pos.x, WIN_HEIGHT / 2 - pos.y);
	if (diff.x)
		turn_left_right(c, diff.x * -0.001);
	if (diff.y)
		look_up_down(c, diff.y);
	mlx_set_mouse_pos(mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}