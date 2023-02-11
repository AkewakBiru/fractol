/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:36:24 by abiru             #+#    #+#             */
/*   Updated: 2023/02/11 17:23:18 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	mandelbrot(t_rng *rng, t_complex *c, int x, int y)
{
	int			iter;
	double		tmp;
	t_complex	z;
	int			is_inside;

	iter = -1;
	z.re = c->re;
	z.im = c->im;
	is_inside = 1;
	while (++iter < rng->max_iter)
	{
		tmp = z.re * z.re - z.im * z.im + c->re;
		if (z.re * z.re + z.im * z.im >= 4)
		{
			is_inside = 0;
			break ;
		}
		z.im = 2 * z.re * z.im + c->im;
		z.re = tmp;
	}
	if (is_inside)
		my_mlx_pixel_put(&(rng->img), x, y, 0);
	else
		my_mlx_pixel_put(&(rng->img), x, y, rng->color * iter);
}

void	julia(t_rng *rng, t_complex *c, int x, int y)
{
	int			iter;
	double		tmp;
	t_complex	z;
	int			is_inside;

	iter = -1;
	z.re = c->re;
	z.im = c->im;
	is_inside = 1;
	while (++iter < rng->max_iter)
	{
		tmp = z.re * z.re - z.im * z.im + rng->jx;
		if (z.re * z.re + z.im * z.im >= 4)
		{
			is_inside = 0;
			break ;
		}
		z.im = 2 * z.re * z.im + rng->jy;
		z.re = tmp;
	}
	if (!is_inside)
		my_mlx_pixel_put(&(rng->img), x, y, ((double)iter / rng->max_iter)
			* rng->color);
	else
		my_mlx_pixel_put(&(rng->img), x, y, 0);
}

void	burning_ship(t_rng *rng, t_complex *c, int x, int y)
{
	int			iter;
	double		tmp;
	t_complex	z;
	int			is_inside;

	iter = -1;
	z.re = c->re;
	z.im = c->im;
	is_inside = 1;
	while (++iter < rng->max_iter)
	{
		tmp = z.re * z.re - z.im * z.im + c->re;
		if (z.re * z.re + z.im * z.im >= 4)
		{
			is_inside = 0;
			break ;
		}
		z.im = -2 * fabs(z.re * z.im) + c->im;
		z.re = tmp;
	}
	if (is_inside)
		my_mlx_pixel_put(&(rng->img), x, y, 0);
	else
		my_mlx_pixel_put(&(rng->img), x, y, rng->color * iter);
}

void	renderer(t_rng *rng)
{
	t_complex	c;
	int			y;
	int			x;

	mlx_clear_window(rng->mlx, rng->win);
	y = -1;
	while (++y < HEIGHT)
	{
		c.im = rng->max_y - y * (rng->max_y - rng->min_y) / (HEIGHT - 1);
		x = -1;
		while (++x < WIDTH)
		{
			c.re = rng->min_x + x * (rng->max_x - rng->min_x) / (WIDTH - 1);
			if (rng->cur_set == 1)
				mandelbrot(rng, &c, x, y);
			else if (rng->cur_set == 2)
				julia(rng, &c, x, y);
			else if (rng->cur_set == 3)
				burning_ship(rng, &c, x, y);
		}
	}
	mlx_put_image_to_window(rng->mlx, rng->win, rng->img.img, 0, 0);
}
