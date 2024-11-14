/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:13:47 by gbertet           #+#    #+#             */
/*   Updated: 2024/11/14 16:38:57 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <errno.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "MLX42/include/MLX42/MLX42_Int.h"
# include "libft/libft.h"
# include "parsing.h"

# define WIN_WIDTH	1200
# define WIN_HEIGHT	800

# define K_ESC		65307
# define K_LEFT		65361
# define K_RIGHT	65363
# define K_UP		65362
# define K_DOWN		65364

# define K_Q		113
# define K_E		101

# define M_SCRL_UP	4
# define M_SRCL_DWN	5

# define P_HITBOX	0.125
# define P_MV_SPEED	0.01

# define PI			3.141592

typedef struct	s_keypress
{
	int up;
	int down;
	int	left;
	int	right;
	int	q;
	int	e;
	int	m;
}				t_keypress;

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_coord
{
	float	x;
	float	y;
}				t_coord;

typedef struct	s_texture
{
	int	*pixels;
	int	width;
	int	height;
}				t_texture;


typedef struct	s_color
{
	t_texture	*no_texture;
	t_texture	*so_texture;
	t_texture	*we_texture;
	t_texture	*ea_texture;
	t_texture	*ce_texture;
	t_texture	*fl_texture;
	int			ceiling_color;
	int			floor_color;
}				t_color;

typedef struct	s_sprite
{
	t_coord		coord;
	t_texture	*texture;
}				t_sprite;


typedef struct	s_ray
{
	int		num;
	t_coord	dir;
	t_coord	sideDist;
	t_coord	deltaDist;
	float	perpWallDist;
	float	wallX;
	t_pos	pos;
	t_pos	step;
	int		texX;
	int		hit;
	int		side;
}				t_ray;

typedef struct	s_camera
{
	t_coord	coord;
	t_coord	dir;
	t_coord	plane;
	t_ray	*rays;
	float	z;
	float	up_down;
	float	move_speed;
	int		is_jumping;
	int		is_landing;
}				t_camera;

typedef struct	s_cub
{
	t_camera	camera;
	t_color		textures;
	t_keypress	key;
	t_data_fd	data;
	mlx_image_t	*render;
	mlx_t		*ptr;
	void		*win;
	int			width;
	int			height;
	char		**map;
}				t_cub;

t_coord		fill_coord(float x, float y);
t_pos		fill_pos(int x, int y);
void		draw_line(mlx_image_t *data, t_coord begin, t_coord end, int color);
void		draw_rectangle(mlx_image_t *data, t_pos begin, t_pos end, int color);
void		draw_wall_texture(t_cub *cub, t_ray ray, int drawStart, int lineLength, int drawEnd);
int			rgba_value(int r, int g, int b, int a);
int			ft_exit(t_cub *cub, int err);
char		**get_map();
void		render_all(t_cub *cub);
int 		ft_abs(int i);
void    	ft_freestr(char **str);
void    	ft_fswap(float *a, float *b);
float   	ft_fabs(float x);
int			get_ray_color(t_ray ray);
void		draw_rays(t_cub *cub);
void		init_keypress(t_cub *cub);
void		da_key_hook(mlx_key_data_t keydata, void *thing);

void		init_camera(t_camera *c, t_pos pos, char dir);
int			init_cub(t_cub *cub);

void		show_fps(t_cub *cub, double delta);

void		draw_single_ray(t_cub *cub, t_ray ray, int col);
void		draw_rays_map(t_cub *cub);
void		draw_ceiling_line(t_cub *cub, t_coord coord, t_coord step, int y);
void		draw_floor_line(t_cub *cub, t_coord coord, t_coord step, int y);

void		turn_left_right(t_camera *c, float speed);
void		look_up_down(t_camera *c, int speed);
void		move_right(t_camera *c, char **map);
void		move_left(t_camera *c, char **map);
void		move_down(t_camera *c, char **map);
void		move_up(t_camera *c, char **map);
void		jump(t_camera *c, int speed);
void		set_momentum(t_camera *c);
void		mouse_support(mlx_t *mlx, t_camera *c);

t_texture	*get_side_texture(int side, float dirX, float dirY, t_color texture);
void		load_textures(t_cub *cub);
t_texture	*get_texture(t_cub *cub, char *path);
void		draw_texture(t_cub *cub, t_texture texture, t_pos pos);
void		free_textures(t_color *textures);

void		get_side_dist(t_camera cam, t_ray *ray);
void		dda_loop(t_ray *ray, char **map);
void		get_wall_data(t_camera cam, t_ray *ray);
void		get_rays(t_cub *cub, t_ray *rays, int width);

void		cast_floor_ceiling(t_cub *cub, t_camera cam);

#endif
