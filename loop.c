#include "mlx/mlx.h"
#include "fractol.h"

int palette[5] = {
					(0 << 16 | 7 << 8 | 100), (32 << 16 | 107 << 8 | 203), (237 << 16 | 255 << 8 | 255)
					, (255 << 16 | 170 << 8 | 0), (0 << 16 | 2 << 8 | 0)};

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
		my_mlx_pixel_put(&(rng->img), x, y, 0x00000000);
	else
		my_mlx_pixel_put(&(rng->img), x, y, ((((int)(log(iter)) | iter) << iter)));
}

void julia(t_rng *rng, t_complex *c, int x, int y)
{
	int	iter;
	double	tmp;
	t_complex	z;
	int	is_inside;

	iter = -1;
	z.re = c->re;
	z.im = c->im;
	is_inside = 1;
	while (++iter < rng->max_iter)
	{
		tmp = z.re * z.re - z.im * z.im + ((rng->mpx - WIDTH / 2) / WIDTH);
		if (z.re * z.re + z.im * z.im >= 4)
		{
			is_inside = 0;
			break ;
		}
		z.im = 2 * z.re * z.im + ((rng->mpy - HEIGHT / 2) / HEIGHT);
		z.re = tmp;
	}
	// if (is_inside)
	// 	my_mlx_pixel_put(&(rng->img), x, y, 0x000022FF);
	// else
		my_mlx_pixel_put(&(rng->img), x, y, palette[iter % 5]);
}

void	renderer(t_rng *rng)
{
	t_complex	c;
	int		y;
	int		x;
	int		iter;

	mlx_clear_window(rng->mlx, rng->win);
	y = -1;
	while (++y < HEIGHT)
	{
		c.im = rng->max_y - y * (rng->max_y - rng->min_y) / (HEIGHT - 1);
		x = -1;
		while (++x < WIDTH)
		{
			// get_mouse_posn(rng);
			c.re = rng->min_x + x * (rng->max_x - rng->min_x) / (WIDTH - 1);
			if (rng->cur_set == 1)
				mandelbrot(rng, &c, x, y);
			else if (rng->cur_set == 2)
				julia(rng, &c, x, y);
// 			double z_re = c_re;
// 			double z_im = c_im;
// 			int isInside = 1;
// 			iter = -1;
// 			while (++iter < rng->max_iter)
// 			{
// 				double tmp = z_re * z_re - z_im * z_im + c_re;
// 				if (z_re * z_re + z_im * z_im >= 4)
// 				{
// 					isInside = 0;
// 					break ;
// 				}
// 				z_im = 2 * z_re * z_im + c_im;
// 				z_re = tmp;
// 			}
// 			if (isInside)
// 				my_mlx_pixel_put(&(rng->img), x, y, 0x00000000);
// 			else
// // my_mlx_pixel_put(&(rng->img), x, y, (((((int)(log(n)) | n) << n)) << 16 | ((((int)(log(n)) | n) << n)) << 8 | ((((int)(log(n)) | palette[n % 5]) << n)) << 8));
// 				my_mlx_pixel_put(&(rng->img), x, y, ((((int)(log(iter)) | iter) << iter)));
		}
	}
	mlx_put_image_to_window(rng->mlx, rng->win, rng->img.img, 0, 0);
}

int	get_mouse_posn(int x, int y, t_rng *rng)
{
	rng->mpx = x;
	rng->mpy = y;
	renderer(rng);
}

int	close_win(t_rng *vars)
{
	if (vars->mlx && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	free(vars);
	exit(0);
}

double transpose(double x, double y, double i)
{
	return (x + ((y - x)) * i);
}

int zoom(int code, int x, int y, t_rng *rng)
{
	double	pos_x;
	double	pos_y;

	if (code != 4 && code != 5)
		return (0);
	pos_x = (double)(x / (WIDTH / (rng->max_x - rng->min_x) + rng->min_x));
	pos_y = (double)(x / (HEIGHT / (rng->max_y - rng->min_y)) * -1 + rng->max_y);
	double zoom;
	double i = 0.0;
	if (code == 4)
		zoom = 0.80;
	else if (code == 5)
		zoom = 1.20;
	i = 1.0 / zoom;
	rng->min_x = transpose(pos_x, rng->min_x, i);
	rng->max_x = transpose(pos_x, rng->max_x, i);
	rng->min_y = transpose(pos_y, rng->min_y, i);
	rng->max_y = transpose(pos_y, rng->max_y, i);
	renderer(rng);
}

int key_handler(int keycode, t_rng *rng)
{
	if (keycode == 53)
		close_win(rng);
	if (keycode == 123)
	{
		rng->min_x -= 0.1;
		rng->max_x -= 0.1;
	}
	else if (keycode == 124)
	{
		rng->min_x += 0.1;
		rng->max_x += 0.1;
	}
	else if (keycode == 125)
	{
		rng->min_y += 0.1;
		rng->max_y += 0.1;
	}
	else if (keycode == 126)
	{
		rng->min_y -= 0.1;
		rng->max_y -= 0.1;
	}
	renderer(rng);
}

void display_params(t_rng	*rng)
{
	ft_putstr_fd("Usage: ./fractol OPTIONS - [mandelbrot, julia]\n", 1);
	if (rng)
		free(rng);
	exit(0);
}

void draw_fractal(int ac, char **av, t_rng *rng)
{
	if (ft_strncmp(av[1], "mandelbrot", ft_strlen(av[1])) == 0)
		rng->cur_set = 1;
	else if (ft_strncmp(av[1], "julia", ft_strlen(av[1])) == 0)
		rng->cur_set = 2;
	renderer(rng);
}

int main(int ac, char **av)
{
	t_rng	*rng;

	if (ac < 2)
		display_params(NULL);
	rng = (t_rng *)malloc(sizeof(t_rng));
	if (!rng)
		exit(0);
	rng->min_x = -2.0;
	rng->max_x = 1.0;
	rng->min_y = -1.2;
	rng->max_iter = 100;
	rng->max_y = rng->min_y + (rng->max_x - rng->min_x) * (HEIGHT) / (WIDTH);
	rng->mlx = mlx_init();
	rng->win = mlx_new_window(rng->mlx, WIDTH, HEIGHT, "fractal");
	rng->img.img = mlx_new_image(rng->mlx, WIDTH, HEIGHT);
	rng->img.addr = mlx_get_data_addr(rng->img.img, &rng->img.bits_per_pixel, &rng->img.line_length, &rng->img.endian);
	draw_fractal(ac, av, rng);
	mlx_hook(rng->win, 2, 0, key_handler, rng);
	mlx_hook(rng->win, 17, 0, close_win, rng);
	mlx_mouse_hook(rng->win, zoom, rng);
	mlx_hook(rng->win, 6, 0, get_mouse_posn, rng);
	mlx_loop(rng->mlx);
}
