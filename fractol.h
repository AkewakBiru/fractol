/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:55:10 by abiru             #+#    #+#             */
/*   Updated: 2023/01/27 13:41:30 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1000
# define HEIGHT 1000
# include "mlx/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_rng
{
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	unsigned int	color;
	int				max_iter;
	int				cur_set;
	double			mpx;
	double			mpy;
	double			jx;
	double			jy;
	void			*win;
	void			*mlx;
	t_data			img;
}	t_rng;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
double	get_float(const char *str, int start, int sign);
double	ft_atof(const char *str);
int		close_win(t_rng *vars);
void	display_error(char *str);
void	show_usage(void);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	mandelbrot(t_rng *rng, t_complex *c, int x, int y);
void	julia(t_rng *rng, t_complex *c, int x, int y);
void	burning_ship(t_rng *rng, t_complex *c, int x, int y);
void	renderer(t_rng *rng);
void	move_julia(int key, t_rng	*rng);
void	check_input(int ac, char **av, t_rng *rng);
void	init_mlx(t_rng *rng, char **av);
void	init_corner(t_rng *rng);
#endif
