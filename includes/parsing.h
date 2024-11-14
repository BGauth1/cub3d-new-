/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbertet <gbertet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:42:04 by gbertet           #+#    #+#             */
/*   Updated: 2023/10/20 15:43:37 by gbertet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_data_fd
{
	char			**tab;
	struct s_map	*input;
	char			*path_no;
	char			*path_so;
	char			*path_we;
	char			*path_ea;
	int				*f;
	int				*c;
}				t_data_fd;

typedef struct s_map
{
	int		x;
	int		y;
	int		j;
	int		i;
	int		m;
	int		pos_s[2];
	char	pos_j;
}				t_map;

//	ft_parsing.c	//
int			parsing_data(int argc, char **argv, t_data_fd *data);

//	ft_parsing_color.c	//
int			parsing_colors(char *line, t_data_fd *data, int id);

//	ft_parsing_color_error.c	//
int			check_digit_error(char *line);
int			check_data_rgb_error(char *line, int i);
int			check_path_file(char *path, char *format);

//	ft_parse_line_break.c	//
int			ft_parse_line_split(char *line, t_data_fd *data);

//	ft_parsing_texture.c	//
int			check_fake(char *line);
int			rec_pos_element(char *line);
int			check_id(char *line);
int			parsing_texture(char *line, t_data_fd *data, int id);

//	ft_parsing_texture_error.c	//
int			printf_error(int id, char *str);
int			check_end_line_texture(char *line, int i, char *path, int len);
int			check_path_texture(char *path, int id);
int			check_nb_element(t_data_fd *data, int id);
int			check_if_all_init(t_data_fd *data, char *line);

//	ft_init_struct.c	//
void		ft_free_struct(t_data_fd *data);
void		ft_init_struct(t_data_fd *data);
void		ft_init_tab_map(t_data_fd *data);
void		ft_free_tab_map(t_data_fd *data);

//	ft_parsing_map.c	//
int			ft_find_map(char *line);
int			ft_parsing_map(t_data_fd *data, char *line);

//	ft_parsing_map_utils.c	//
int			first_read_map(char *path, t_data_fd *data);
int			check_pts_card(char c);
int			ft_complet_map(char *line);

//	ft_parsing_map_error.c	//
int			second_read_map(t_data_fd *data);