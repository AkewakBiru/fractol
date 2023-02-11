/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:30:14 by abiru             #+#    #+#             */
/*   Updated: 2023/01/27 15:23:28 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	validate_julia(int ac, char **av, t_rng *rng)
{
	if (ac != 4)
		display_error("Usage: ./fractol julia [pos_x] [pos_y]\n");
	if ((int)ft_atof(av[2]) == 3)
		display_error("Allowed range is between (-1, 1)\n");
	else if (av[2])
		rng->jx = ft_atof(av[2]);
	if ((int)ft_atof(av[3]) == 3)
		display_error("Allowed range is between (-1, 1)\n");
	else if (av[3])
		rng->jy = ft_atof(av[3]);
	rng->cur_set = 2;
}

void	check_input(int ac, char **av, t_rng *rng)
{
	if (ac < 2 || ac > 4)
		show_usage();
	if (ft_strcmp(av[1], "mandelbrot") == 0)
	{
		if (ac != 2)
			display_error("mandelbrot set needs 1 argument only\n");
		rng->cur_set = 1;
	}
	else if (ft_strcmp(av[1], "julia") == 0)
		validate_julia(ac, av, rng);
	else if (ft_strcmp(av[1], "burning ship") == 0)
	{
		if (ac != 2)
			display_error("burning ship needs 1 argument only\n");
		rng->cur_set = 3;
	}
	else
		show_usage();
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

void	init_mlx(t_rng *rng, char **av)
{
	rng->mlx = mlx_init();
	if (!rng->mlx)
		exit(1);
	rng->win = mlx_new_window(rng->mlx, WIDTH, HEIGHT, av[1]);
	if (!rng->win)
		exit(1);
	rng->img.img = mlx_new_image(rng->mlx, WIDTH, HEIGHT);
	if (!rng->img.img)
		close_win(rng);
	rng->img.addr = mlx_get_data_addr(rng->img.img, &(rng->img.bits_per_pixel),
			&(rng->img.line_length), &(rng->img.endian));
	if (!rng->img.addr)
		close_win(rng);
}

void	init_corner(t_rng *rng)
{
	if (rng->cur_set == 1)
	{
		rng->min_x = -2.4;
		rng->max_x = 1.8;
		rng->min_y = -2.0;
	}
	else if (rng->cur_set == 2)
	{
		rng->min_x = -2.5;
		rng->max_x = 2;
		rng->min_y = -2;
	}
	else if (rng->cur_set == 3)
	{
		rng->min_x = -2;
		rng->max_x = 2;
		rng->min_y = -1.8;
	}
	rng->max_y = rng->min_y + (rng->max_x - rng->min_x) * (HEIGHT) / (WIDTH);
	return ;
}
