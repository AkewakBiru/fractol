/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:30:29 by abiru             #+#    #+#             */
/*   Updated: 2023/01/16 16:19:21 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

#include <math.h>

// void DrawCircle(int x, int y, int r, int color)
// {
//       static const double PI = 3.1415926535;
//       double i, angle, x1, y1;

//       for(i = 0; i < 360; i += 0.1)
//       {
//             angle = i;
//             x1 = r * cos(angle * PI / 180);
//             y1 = r * sin(angle * PI / 180);
//             my_mlx_pixel_put(x + x1, y + y1, color);
//       }
// }

unsigned char palette(int iter)
{
	return ((unsigned char)(0x00FF0000 >> iter));
}

#include <stdio.h>
int close(int keycode, t_vars *vars)
{
	(void)keycode;
	printf("%d\n", keycode);
	if (keycode == 53 || keycode == 51)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	// establishes a connection to the correct graphical system and will return a void * which holds the location of 
	// the current MLX instance. (simply initializes minilibx).
	vars.mlx = mlx_init();

	// creates a new window, first arg is the instance of the window initialized, then width and height and title follow resp.
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");

	// creates a new image
	img.img = mlx_new_image(vars.mlx, 1920, 1080);

	// sets the bpp, line_length and endian for the image
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	for (int i = 0;i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			float x = 0.0;
			float y = 0.0;
			int iter = 0;
			int max = 1000;
			while (x * x + y * y <= 2 * 2 && iter < max)
			{
				int xtemp = x * x - y * y - 2;
				y = 2 * x * y - 1.12;
				x = xtemp;
				iter++;
			}
			my_mlx_pixel_put(&img, i, j, 0x00FF0000);
		}
	}

	// for (int i = 0;i < 1920; i++)
	// {
	// 	for (int j = 0; j < 1080; j++)
	// 	{
	// 		my_mlx_pixel_put(&img, i, j, 0x00FF0000);
	// 	}
	// }

	// for (int i = 0; i < 50; i++)
	// {
	// 	my_mlx_pixel_put(&img, 15, 15 + i, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 15 + i, 15, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 65, 15 + i, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 15 + i, 65, 0x00FF0000);
	// }

	// for (int i = 0; i < 50; i++)
	// {
	// 	my_mlx_pixel_put(&img, 100 - i, 204 - i, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 50 - i, 154 + i, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 50 + i, 204, 0x00FF0000);
	// 	my_mlx_pixel_put(&img, 0 + i, 204, 0x00FF0000);
	// }

    //   static const double PI = 3.1415926535;
    //   double i, angle, x1, y1;
	//   int r = 100;
	//   int y = 500;
	//   int x = 500;

    //   for(i = 0; i < 360; i += 0.1)
    //   {
    //         angle = i;
    //         x1 = r * cos(angle * PI / 180);
    //         y1 = r * sin(angle * PI / 180);
    //         my_mlx_pixel_put(&img, x + x1, y + y1, 0x00FF0000);
    //   }
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 02, 1L<<0, close, &vars);
	mlx_loop(vars.mlx);
}
