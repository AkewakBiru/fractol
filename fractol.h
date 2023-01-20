#ifndef FRACTOL_H
# define FRACTOL_H
# define WIDTH 1080
# define HEIGHT 900
#include "mlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

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
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	int		max_iter;
	int		cur_set;
	double		mpx;
	double		mpy;
	void	*win;
	void	*mlx;
	t_data	img;
}	t_rng;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;



void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
#endif
