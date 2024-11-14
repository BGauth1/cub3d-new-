/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:48:31 by gbertet           #+#    #+#             */
/*   Updated: 2023/11/02 14:33:52 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_ray(t_camera cam, t_ray *ray, int iter)
{
	float	camera;

	camera = 2 * iter / (float)WIN_WIDTH - 1;
	ray->dir.x = cam.dir.x + cam.plane.x * camera;
	ray->dir.y = cam.dir.y + cam.plane.y * camera;
	ray->pos.x = (int)cam.coord.x;
	ray->pos.y = (int)cam.coord.y;
	if (ray->dir.x == 0)
		ray->deltaDist.x = 1e30;
	else
		ray->deltaDist.x = ft_fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->deltaDist.y = 1e30;
	else
		ray->deltaDist.y = ft_fabs(1 / ray->dir.y);
	ray->hit = 0;
}

void	get_side_dist(t_camera cam, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (cam.coord.x - (float)ray->pos.x)
			* ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = ((float)ray->pos.x + 1.0
				- cam.coord.x) * ray->deltaDist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (cam.coord.y - (float)ray->pos.y)
			* ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = ((float)ray->pos.y + 1.0
				- cam.coord.y) * ray->deltaDist.y;
	}
}

void	dda_loop(t_ray *ray, char **map)
{
	while (ray->hit == 0)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
		if (map[ray->pos.y][ray->pos.x] != '0')
			ray->hit = 1;
	}
}

void	get_wall_data(t_camera cam, t_ray *ray)
{
	if (!ray->side)
	{
		ray->perpWallDist = ray->sideDist.x - ray->deltaDist.x;
		ray->wallX = cam.coord.y + ray->perpWallDist * ray->dir.y;
	}
	else
	{
		ray->perpWallDist = ray->sideDist.y - ray->deltaDist.y;
		ray->wallX = cam.coord.x + ray->perpWallDist * ray->dir.x;
	}
	ray->wallX -= (int)ray->wallX;
	ray->wallX = 1 - ray->wallX;
}

void	get_rays(t_cub *cub, t_ray *rays, int width)
{
	int	i;

	i = -1;
	while (++i < width)
	{
		init_ray(cub->camera, &rays[i], i);
		get_side_dist(cub->camera, &rays[i]);
		dda_loop(&rays[i], cub->map);
		get_wall_data(cub->camera, &rays[i]);
		draw_single_ray(cub, cub->camera.rays[i], width - i - 1);
	}
	i = -1;
	if (cub->key.m)
		draw_rays_map(cub);			
}
