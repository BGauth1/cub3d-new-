/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:46:30 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/20 16:56:17 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_texture	*get_side_texture(int side, float dirX, float dirY, t_color txtr)
{
	if (side == 1 && dirY > 0)
		return (txtr.so_texture);
	else if (side == 0 && dirX > 0)
		return (txtr.ea_texture);
	else if (side == 1)
		return (txtr.no_texture);
	return (txtr.we_texture);
}

t_texture	*get_texture_from_mlx(mlx_image_t *tmp)
{
	t_texture	*texture;
	int			tot_pixels;
	int			hpos;
	int			bpos;

	if (!tmp)
		return (NULL);
	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->pixels = malloc ((tmp->height * tmp->width) * sizeof(int));
	if (!texture->pixels)
		return (NULL);
	texture->height = tmp->height;
	texture->width = tmp->width;
	hpos = -1;
	bpos = 0;
	tot_pixels = tmp->height * tmp->width * 4;
	while (bpos < tot_pixels)
	{
		texture->pixels[++hpos] = rgba_value(tmp->pixels[bpos], tmp->pixels
			[bpos + 1], tmp->pixels[bpos + 2], tmp->pixels[bpos + 3]);
		bpos += 4;
	}
	return (texture);
}

t_texture	*get_texture(t_cub *cub, char *path)
{
	t_texture		*texture;
	mlx_texture_t	*mlx_texture_tmp;
	mlx_image_t		*mlx_image_tmp;

	mlx_texture_tmp = mlx_load_png(path);
	if (mlx_texture_tmp)
	{
		mlx_image_tmp = mlx_texture_to_image(cub->ptr, mlx_texture_tmp);
		if (mlx_image_tmp)
			texture = get_texture_from_mlx(mlx_image_tmp);
		else
			texture = NULL;
		mlx_delete_texture(mlx_texture_tmp);
		mlx_delete_image(cub->ptr, mlx_image_tmp);
		return (texture);
	}
	ft_printf("MLX42: Couldn't load \"%s\".\n", path);
	return (NULL);
}

void	load_textures(t_cub *cub)
{
	cub->textures.no_texture = get_texture(cub, cub->data.path_no);
	cub->textures.so_texture = get_texture(cub, cub->data.path_so);
	cub->textures.ea_texture = get_texture(cub, cub->data.path_ea);
	cub->textures.we_texture = get_texture(cub, cub->data.path_we);
}

void	draw_texture(t_cub *cub, t_texture texture, t_pos pos)
{
	int	x;
	int	y;
	int	limit_x;
	int	limit_y;

	y = -1;
	limit_x = WIN_WIDTH - pos.x;
	limit_y = WIN_HEIGHT - pos.y;
	while (++y < texture.height && y < limit_y)
	{
		x = -1;
		while (++x < texture.width && x < limit_x)
			mlx_put_pixel(cub->render, x + pos.x, y + pos.y,
				texture.pixels[x + y * texture.width]);
	}
}

void	free_textures(t_color *textures)
{
	if (textures->no_texture)
	{
		if (textures->no_texture->pixels)
			free(textures->no_texture->pixels);
		free(textures->no_texture);
	}
	if (textures->so_texture)
	{
		if (textures->so_texture->pixels)
			free(textures->so_texture->pixels);
		free(textures->so_texture);
	}
	if (textures->ea_texture)
	{
		if (textures->ea_texture->pixels)
			free(textures->ea_texture->pixels);
		free(textures->ea_texture);
	}
	if (textures->we_texture)
	{
		if (textures->we_texture->pixels)
			free(textures->we_texture->pixels);
		free(textures->we_texture);
	}
	if (textures->ce_texture)
	{
		if (textures->ce_texture->pixels)
			free(textures->ce_texture->pixels);
		free(textures->ce_texture);
	}
	if (textures->fl_texture)
	{
		if (textures->fl_texture->pixels)
			free(textures->fl_texture->pixels);
		free(textures->fl_texture);
	}
}
