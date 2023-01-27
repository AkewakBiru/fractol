/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:55:00 by abiru             #+#    #+#             */
/*   Updated: 2023/01/27 13:41:04 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	adjust_iteration(int keycode, t_rng	*rng)
{
	if (keycode == 35)
	{
		if (rng->max_iter <= 1000)
			rng->max_iter += 20;
		else
		{
			write(2, "\033[0;32m", 9);
			write(2, " Maximum iteration reached\n",
				ft_strlen(" Maximum iteration reached\n"));
		}
	}
	else if (keycode == 27)
	{
		if (rng->max_iter >= 100)
			rng->max_iter -= 20;
		else
		{
			write(2, "\033[0;32m", 9);
			write(2, " Maximum iteration reached\n",
				ft_strlen(" Maximum iteration reached\n"));
		}
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
	renderer(rng);
	return (0);
}

void	key_handler2(int keycode, t_rng *rng, t_complex *tmp)
{
	if (keycode == 124)
	{
		rng->min_x -= 0.1 * tmp->re;
		rng->max_x -= 0.1 * tmp->re;
	}
	else if (keycode == 125)
	{
		rng->min_y += 0.1 * tmp->im;
		rng->max_y += 0.1 * tmp->im;
	}
	else if (keycode == 126)
	{
		rng->min_y -= 0.1 * tmp->im;
		rng->max_y -= 0.1 * tmp->im;
	}
	else if (keycode == 8)
	{
		if (rng->color >= 2147483647 || (int)(rng->color * log(10)) >> 1 <= 128)
			rng->color = 0x160C1D;
		else
			rng->color = (int)(rng->color * log(10)) >> 1;
	}
}

int	key_handler(int keycode, t_rng *rng)
{
	t_complex	tmp;

	tmp.re = fabs(rng->max_x - rng->min_x);
	tmp.im = fabs(rng->max_y - rng->min_y);
	if (keycode == 53)
		close_win(rng);
	else if (keycode == 27 || keycode == 35)
		adjust_iteration(keycode, rng);
	else if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
		move_julia(keycode, rng);
	else if (keycode == 123)
	{
		rng->min_x += 0.1 * tmp.re;
		rng->max_x += 0.1 * tmp.re;
	}
	else if (keycode == 124 || keycode == 125 || keycode == 126 || keycode == 8)
		key_handler2(keycode, rng, &tmp);
	else
		return (0);
	renderer(rng);
	return (0);
}

int	main(int ac, char **av)
{
	t_rng	rng;

	check_input(ac, av, &rng);
	init_corner(&rng);
	rng.max_iter = 300;
	rng.color = 0x160C1D;
	init_mlx(&rng, av);
	renderer(&rng);
	mlx_hook(rng.win, 2, 0, key_handler, &rng);
	mlx_hook(rng.win, 17, 0, close_win, &rng);
	mlx_mouse_hook(rng.win, zoom, &rng);
	mlx_loop(rng.mlx);
	return (0);
}
