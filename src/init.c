/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:57:50 by gbertet           #+#    #+#             */
/*   Updated: 2023/11/02 14:44:47 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	starting_direction(t_camera *c, char ch)
{
	if (ch == 'N')
	{
		c->dir = fill_coord(0, -1);
		c->plane = fill_coord(-0.66, 0);
	}
	else if (ch == 'S')
	{
		c->dir = fill_coord(0, 1);
		c->plane = fill_coord(0.66, 0);
	}
	else if (ch == 'E')
	{
		c->dir = fill_coord(1, 0);
		c->plane = fill_coord(0, -0.66);
	}
	else
	{
		c->dir = fill_coord(-1, 0);
		c->plane = fill_coord(0, 0.66);
	}
}

void	init_camera(t_camera *c, t_pos pos, char dir)
{
	int	i;
	
	c->coord = fill_coord(pos.x + 0.5, pos.y + 0.5);
	starting_direction(c, dir);
	c->up_down = 0;
	c->z = 0;
	c->is_jumping = 0;
	c->is_landing = 0;
	c->move_speed = P_MV_SPEED;
	c->rays = malloc((WIN_WIDTH) * sizeof(t_ray));
	i = -1;
	while (++i < WIN_WIDTH)
		c->rays[i].num = WIN_WIDTH - i - 1;
}

int	init_cub(t_cub *cub)
{
	cub->width = WIN_WIDTH;
	cub->height = WIN_HEIGHT;
	cub->ptr = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3d", false);
	cub->render = mlx_new_image(cub->ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_set_mouse_pos(cub->ptr, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(cub->ptr, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(cub->ptr, cub->render, 0, 0);
	init_camera(&cub->camera, fill_pos(cub->data.input->pos_s[0], cub->data.input->pos_s[1]), cub->data.input->pos_j);
	init_keypress(cub);
	cub->map = cub->data.tab;
	cub->map[cub->data.input->pos_s[1]][cub->data.input->pos_s[0]] = '0';
	cub->textures.ceiling_color = rgba_value(228, 228, 118, 255);
	cub->textures.floor_color = rgba_value(203, 203, 90, 255);
	cub->textures.fl_texture = get_texture(cub, "textures/backroom-floor.png");
	cub->textures.ce_texture = get_texture(cub, "textures/backroom-ceiling.png");
	load_textures(cub);
	if (!cub->textures.ea_texture || !cub->textures.so_texture
		|| !cub->textures.no_texture || !cub->textures.we_texture)
		return (2);
	return (0);
}
