/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:59:54 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/31 16:52:35 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	show_fps(t_cub *cub, double delta)
{
	static double		time = 0;
	static int			nb_frame = 0;
	static char			*fps = NULL;
	static mlx_image_t	*fps_counter = NULL;

	if (!fps)
	{
		fps = ft_strdup("0");
		fps_counter = mlx_put_string(cub->ptr, fps, 10, 10);
	}
	time += delta;
	nb_frame++;
	if (time >= 1.0)
	{
		if (fps)
			free(fps);
		fps = ft_itoa(1 / (time / nb_frame));
		time -= 1.0;
		nb_frame = 0;
		if (fps_counter)
			mlx_delete_image(cub->ptr, fps_counter);
		fps_counter = mlx_put_string(cub->ptr, fps, 10, 10);
	}
}

// void	display_info(t_cub *cub, t_pos pos, char *info)
// {
// 	static mlx_image_t	*
// }