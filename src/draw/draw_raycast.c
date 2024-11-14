/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:46:29 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/31 17:09:39 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_wall_texture(t_cub *cub, t_ray ray, int drawStart,
	int lineLength, int drawEnd)
{
	t_texture	*texture;
	int			tex_x;
	int			tex_y;
	float		step;
	float		texpos;

	texture = get_side_texture(ray.side, ray.dir.x, ray.dir.y, cub->textures);
	tex_x = (int)(ray.wallX * (float)texture->width);
	if ((!ray.side && ray.dir.x > 0) || (ray.side && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	step = 1.0 * texture->height / lineLength;
	texpos = (drawStart - WIN_HEIGHT / 2 + lineLength / 2 - cub->camera.up_down - (cub->camera.z / ray.perpWallDist)) * step;
	while (drawStart < drawEnd)
	{
		tex_y = (int)texpos;
		texpos += step;
		mlx_put_pixel(cub->render, ray.num, drawStart,
			texture->pixels[texture->width * tex_y + tex_x]);
		drawStart++;
	}
}

void	draw_single_ray(t_cub *cub, t_ray ray, int col)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	drawceil;
	(void) col;

	lineheight = (int)(WIN_HEIGHT / ray.perpWallDist);
	drawstart = -lineheight / 2 + WIN_HEIGHT / 2 + cub->camera.up_down + (cub->camera.z / ray.perpWallDist);
	if (drawstart < 0)
		drawstart = 0;
	if (drawstart < WIN_HEIGHT - 1)
	{
		drawend = lineheight / 2 + WIN_HEIGHT / 2 + cub->camera.up_down + (cub->camera.z / ray.perpWallDist);
		if (drawend >= WIN_HEIGHT)
			drawend = WIN_HEIGHT - 1;
		drawceil = 0;
		draw_wall_texture(cub, ray, drawstart, lineheight, drawend);
	}	
}

void	draw_rays_map(t_cub *cub)
{
	int	color;
	int	i;

	i = -1;
	while (++i < WIN_WIDTH)
	{
		color = get_ray_color(cub->camera.rays[i]);
		draw_line(cub->render, fill_coord(cub->camera.coord.x * 40, cub
				->camera.coord.y * 40), fill_coord(cub->camera.coord.x
				* 40.0 + cub->camera.rays[i].dir.x * cub->camera.rays[i]
				.perpWallDist * 40.0, cub->camera.coord.y * 40.0 + cub
				->camera.rays[i].dir.y * cub->camera.rays[i].perpWallDist
				* 40.0), color);
	}
}

void	draw_ceiling_line(t_cub *cub, t_coord coord, t_coord step, int y)
{
	int		x;
	t_pos	tex_pos_c;
	t_pos	pos;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		pos = fill_pos((int)coord.x, (int)coord.y);
		tex_pos_c = fill_pos(ft_abs((int)(cub->textures.ce_texture->width * (coord.x - pos.x) * 2) % cub->textures.ce_texture->width),
			ft_abs((int)(cub->textures.ce_texture->height * (coord.y - pos.y) * 2) % cub->textures.ce_texture->height));
		coord.x += step.x;
		coord.y += step.y;
		mlx_put_pixel(cub->render, x, y,
			cub->textures.ce_texture->pixels[cub->textures.ce_texture->width * tex_pos_c.y + tex_pos_c.x]);
	}
}

void	draw_floor_line(t_cub *cub, t_coord coord, t_coord step, int y)
{
	int		x;
	int		line;
	t_pos	tex_pos_f;
	t_pos	pos;

	x = -1;
	line = WIN_HEIGHT - y - 1;
	while (++x < WIN_WIDTH)
	{
		pos = fill_pos((int)coord.x, (int)coord.y);
		tex_pos_f = fill_pos(ft_abs((int)(cub->textures.fl_texture->width * (coord.x - pos.x)) % cub->textures.fl_texture->width),
			ft_abs((int)(cub->textures.fl_texture->height * (coord.y - pos.y)) % cub->textures.fl_texture->height));
		coord.x += step.x;
		coord.y += step.y;
		mlx_put_pixel(cub->render, x, line,
			cub->textures.fl_texture->pixels[cub->textures.fl_texture->width * tex_pos_f.y + tex_pos_f.x]);
	}
}
