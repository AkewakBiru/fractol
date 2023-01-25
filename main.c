/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:55:00 by abiru             #+#    #+#             */
/*   Updated: 2023/01/25 19:11:59 by abiru            ###   ########.fr       */
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

void burning_ship(t_rng *rng, t_complex *c, int x, int y)
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

void	move_julia(int key, t_rng	*rng)
{
	if (key == 13)
	{
		if (rng->jy >= -1)
			rng->jy -= 0.01;
	}
	else if (key == 0)
	{
		if (rng->jx >= -1)
			rng->jx -= 0.01;
	}
	else if (key == 1)
	{
		if (rng->jy <= 1)
			rng->jy += 0.01;
	}
	else if (key == 2)
	{
		if (rng->jx <= 1)
			rng->jx += 0.01;
	}
	renderer(rng);
}

int	close_win(t_rng *vars)
{
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	adjust_iteration(int keycode, t_rng	*rng)
{
	if (keycode == 35)
	{
		if (rng->max_iter <= 490)
			rng->max_iter += 10;
	}
	else if (keycode == 24)
	{
		if (rng->max_iter >= 60)
			rng->max_iter += 10;
	}
	renderer(rng);
}

int	zoom(int code, int x, int y, t_rng *rng)
{
	double	zoom;

	zoom = 0.0;
	if (code != 4 && code != 5)
		return (0);
	rng->mpx = (double)x / (WIDTH / (rng->max_x - rng->min_x)) + rng->min_x;
	rng->mpy = rng->max_y - (double)y / (HEIGHT / (rng->max_y - rng->min_y));
	if (code == 4)
		zoom = 0.80;
	else if (code == 5)
		zoom = 1.20;
	rng->min_x = rng->mpx + (rng->min_x - rng->mpx) * (1 / zoom);
	rng->max_x = rng->mpx + (rng->max_x - rng->mpx) * (1 / zoom);
	rng->min_y = rng->mpy + (rng->min_y - rng->mpy) * (1 / zoom);
	rng->max_y = rng->mpy + (rng->max_y - rng->mpy) * (1 / zoom);
	// printf("mpy = %lf\tmin_y = %lf\tmax_y = %lf\n", rng->mpy, rng->min_y, rng->max_y);
	if (zoom == 0.80)
		rng->scale -= 0.1;
	else
		rng->scale += 0.1;
	renderer(rng);
	return (0);
}

int	key_handler(int keycode, t_rng *rng)
{
	if (keycode == 53)
		close_win(rng);
	if (keycode == 24 || keycode == 35)
		adjust_iteration(keycode, rng);
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
		move_julia(keycode, rng);
	if (keycode != 123 && keycode != 124 && keycode != 125
		&& keycode != 126 && keycode != 127 && keycode != 8)
		return (0);
	if (keycode == 123)
	{
		rng->min_x += 0.1 / rng->scale;
		rng->max_x += 0.1 / rng->scale;
	}
	else if (keycode == 124)
	{
		rng->min_x -= 0.1 / rng->scale;
		rng->max_x -= 0.1 / rng->scale;
	}
	else if (keycode == 125)
	{
		rng->min_y += 0.1 / rng->scale;
		rng->max_y += 0.1 / rng->scale;
	}
	else if (keycode == 126)
	{
		rng->min_y -= 0.1 / rng->scale;
		rng->max_y -= 0.1 / rng->scale;
	}
	else if (keycode == 8)
	{
		if (rng->color >= 2147483647)
			rng->color = 0x160C1D;
		else if ((int)(rng->color * log(10)) >> 1 <= 128)
			rng->color = 0x160C1D;
		else
			rng->color = (int)(rng->color * log(10)) >> 1;
	}
	renderer(rng);
	return (0);
}

void	display_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	check_input(int ac, char **av, t_rng *rng)
{
	if (ac < 2 || ac > 4)
		display_error("Usage: ./fractol OPTIONS - [mandelbrot, julia, burning ship]\n");
	if (ft_strcmp(av[1], "mandelbrot") == 0)
	{
		if (ac != 2)
			display_error("mandelbrot set needs 1 argument only\n");
		rng->cur_set = 1;
	}
	else if (ft_strcmp(av[1], "julia") == 0)
	{
		if (ac != 4)
			display_error("Usage: ./fractol julia [pos_x] [pos_y]\n");
		if ((int)ft_atol(av[2]) == 3)
			display_error("Allowed range is between (-1, 1)\n");
		else if (av[2])
			rng->jx = ft_atol(av[2]);
		if ((int)ft_atol(av[3]) == 3)
			display_error("Allowed range is between (-1, 1)\n");
		else if (av[3])
			rng->jy = ft_atol(av[3]);
		rng->cur_set = 2;
	}
	else if (ft_strcmp(av[1], "burning ship") == 0)
	{
		if (ac != 2)
			display_error("burning ship needs 1 argument only\n");
		rng->cur_set = 3;
	}
	else
		display_error("Usage: ./fractol OPTIONS - [mandelbrot, julia, burning ship]\n");
}

int	main(int ac, char **av)
{
	t_rng	rng;

	check_input(ac, av, &rng);
	rng.min_x = -2;
	rng.max_x = 1.5;
	rng.min_y = -2.0;
	rng.max_y = rng.min_y + (rng.max_x - rng.min_x) * (HEIGHT) / (WIDTH);
	rng.max_iter = 500;
	rng.scale = 0.75;
	rng.color = 0x160C1D;
	rng.mlx = mlx_init();
	rng.win = mlx_new_window(rng.mlx, WIDTH, HEIGHT, "fractal");
	rng.img.img = mlx_new_image(rng.mlx, WIDTH, HEIGHT);
	rng.img.addr = mlx_get_data_addr(rng.img.img, &(rng.img.bits_per_pixel),
			&(rng.img.line_length), &(rng.img.endian));
	renderer(&rng);
	mlx_hook(rng.win, 2, 0, key_handler, &rng);
	mlx_hook(rng.win, 17, 0, close_win, &rng);
	mlx_mouse_hook(rng.win, zoom, &rng);
	mlx_loop(rng.mlx);
}
