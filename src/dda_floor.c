/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:11:28 by gbertet           #+#    #+#             */
/*   Updated: 2023/11/02 14:51:12 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	single_ray_ceiling(t_cub *cub, t_coord dir0, t_coord dir1, int y)
{
	t_coord	step;
	t_coord	coord;
	float	deltaRow;

	deltaRow = (WIN_HEIGHT / 2 - cub->camera.z) / (WIN_HEIGHT / 2 - y + cub->camera.up_down);
	coord = fill_coord(cub->camera.coord.x + deltaRow * dir0.x, cub->camera.coord.y + deltaRow * dir0.y);
	step = fill_coord(deltaRow * (dir1.x - dir0.x) / WIN_WIDTH, deltaRow * (dir1.y - dir0.y) / WIN_WIDTH);
	draw_ceiling_line(cub, coord, step, y);
}

void	single_ray_floor(t_cub *cub, t_coord dir0, t_coord dir1, int y)
{
	t_coord	step;
	t_coord	coord;
	float	deltaRow;

	deltaRow = (WIN_HEIGHT / 2 + cub->camera.z) / (WIN_HEIGHT / 2 - y - cub->camera.up_down);
	coord = fill_coord(cub->camera.coord.x + deltaRow * dir0.x, cub->camera.coord.y + deltaRow * dir0.y);
	step = fill_coord(deltaRow * (dir1.x - dir0.x) / WIN_WIDTH, deltaRow * (dir1.y - dir0.y) / WIN_WIDTH);
	draw_floor_line(cub, coord, step, y);
}

void	cast_floor_ceiling(t_cub *cub, t_camera cam)
{
	t_coord	dir0;
	t_coord	dir1;
	int		mid;
	int		y;

	dir0 = fill_coord(cam.dir.x + cam.plane.x, cam.dir.y + cam.plane.y);
	dir1 = fill_coord(cam.dir.x - cam.plane.x, cam.dir.y - cam.plane.y);
	mid = 
	y = -1;
	while (++y < (WIN_HEIGHT / 2 - 1 + cub->camera.up_down) && y < WIN_HEIGHT)
		single_ray_ceiling(cub, dir0, dir1, y);
	y = -1;
	while (++y < (WIN_HEIGHT / 2 - 1 - cub->camera.up_down) && y < WIN_HEIGHT)
		single_ray_floor(cub, dir0, dir1, y);
}