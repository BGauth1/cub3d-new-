/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:34 by gbertet           #+#    #+#             */
/*   Updated: 2024/11/14 16:39:41 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_exit(t_cub *cub, int n)
{
	if (n == 2 || !n)
	{
		mlx_terminate(cub->ptr);
		ft_free_tab_map(&cub->data);
		ft_free_struct(&cub->data);
		free_textures(&cub->textures);
	}
	if (!n)
		free(cub->camera.rays);
	exit(n);
}

void	get_inputs(t_cub *cub)
{
	// if (mlx_is_key_down(cub->ptr, MLX_KEY_LEFT_SHIFT))
	// 	cub->camera.move_speed = P_MV_SPEED * 1.70;
	// else
	// 	cub->camera.move_speed = P_MV_SPEED;
	// if (mlx_is_key_down(cub->ptr, MLX_KEY_C))
	// 	cub->camera.move_speed = 0.001;
	// else
	// 	cub->camera.move_speed = P_MV_SPEED;
	if (mlx_is_key_down(cub->ptr, MLX_KEY_S))
		move_down(&cub->camera, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_W))
		move_up(&cub->camera, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_A))
		move_left(&cub->camera, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_D))
		move_right(&cub->camera, cub->map);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_LEFT))
		turn_left_right(&cub->camera, -0.03);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_RIGHT))
		turn_left_right(&cub->camera, 0.03);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_UP))
		look_up_down(&cub->camera, 20);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_DOWN))
		look_up_down(&cub->camera, -20);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_SPACE) || cub->camera.is_jumping)
		jump(&cub->camera, 1);
	if (cub->camera.is_landing)
		set_momentum(&cub->camera);
	if (mlx_is_key_down(cub->ptr, MLX_KEY_ESCAPE))
		mlx_close_window(cub->ptr);
	mouse_support(cub->ptr, &cub->camera);
}

void	game_loop(void *thing)
{
	t_cub	*cub;

	cub = (t_cub *)thing;
	if (cub->key.m)
		render_all(cub);
	get_inputs(cub);
	show_fps(cub, cub->ptr->delta_time);
	cast_floor_ceiling(cub, cub->camera);
	get_rays(cub, cub->camera.rays, WIN_WIDTH);
}

int	main(int ac, char **av)
{
	t_cub		cub;
	t_data_fd	data;
	int			err;

	if (parsing_data(ac, av, &data))
		return (1);
	cub.data = data;
	err = init_cub(&cub);
	if (err)
		ft_exit(&cub, err);
	draw_texture(&cub, *cub.textures.ea_texture, fill_pos(10, 10));
	mlx_loop_hook(cub.ptr, game_loop, &cub);
	mlx_key_hook(cub.ptr, &da_key_hook, &cub);
	mlx_loop(cub.ptr);
	ft_exit(&cub, 0);
	mlx_terminate(cub.ptr);
	return (0);
}
