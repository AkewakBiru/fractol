/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:27:26 by abiru             #+#    #+#             */
/*   Updated: 2023/01/26 22:10:35 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_win(t_rng *vars)
{
	if (vars->img.img)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	display_error(char *str)
{
	write(2, "\033[0;31m", 9);
	write(2, " ", 1);
	write(2, str, ft_strlen(str));
	exit(1);
}

void	show_usage(void)
{
	write(2, "\033[0;32m", 9);
	write(2, "------------------------------------------------------\n",
		ft_strlen("------------------------------------------------------\n"));
	write(2, "Usage: ./fractal [option]\n\n",
		ft_strlen("Usage: ./fractal [option]\n\n"));
	write(2, "Available options\n", ft_strlen("\nAvailable options\n"));
	write(2, "\t1 - mandelbrot\n", ft_strlen("\t1 - mandelbrot\n"));
	write(2, "\t2 - julia\n", ft_strlen("\t2 - julia\n"));
	write(2, "\t3 - 'burning ship'\n\n", ft_strlen("\t3 - 'burning ship'\n\n"));
	write(2, "Available keys\n", ft_strlen("Available keys\n"));
	write(2, "\tc - change set color\n", ft_strlen("\tc - change set color\n"));
	write(2, "\tw, a, s, d - show different parts of julia set\n",
		ft_strlen("\tw, a, s, d - show different parts of julia set\n"));
	write(2, "\tArrow keys - move view\n", ft_strlen("\tArrow keys - move view\n"));
	write(2, "\tp - increase iteration\n", ft_strlen("\tp - increase iteration\n"));
	write(2, "\t'-' - decrease iteration\n",
		ft_strlen("\t'-' - decrease iteration\n"));
	write(2, "\tESC - quit\n\n", ft_strlen("\tESC - quit\n\n"));
	exit(1);
}
