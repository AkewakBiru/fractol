#include "./mlx/mlx.h"
#define X 1000
#define Y 1000
#include <math.h>

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

typedef struct s_point
{
	int x;
	int y;
} t_point;

void	draw_hline(t_data *img, t_point a, t_point b)
{
	int	i;
	int	j;

	i = a.x;
	if (a.y < b.y)
		j = a.y;
	else
		j = b.y;
	while (i <= b.x)
		my_mlx_pixel_put(img, i++, j, 0x00FF0000);
}

void	draw_line(t_data *img, t_point *a, t_point *b)
{
	int	i;
	int	j;
	int	sign;
	int start;

	if (a->x < b->x)
	{
		i = a->x;
		start = 1;
	}
	else
	{
		start = a->x;
		i = b->x;
	}
	if (a->y < b->y)
	{
		sign = 1;
		j = a->y;
	}
	else
	{
		sign = -1;
		j = a->y;
	}
	while (i <= start)
	{
		my_mlx_pixel_put(img, i, j, 0x00FF0000);
		i++;
		j += sign;
	}
}

int main()
{
	t_data img;
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, X, Y, "Triangle");
	img.img = mlx_new_image(mlx, X, Y);
	img.addr = mlx_get_data_addr(img.img, &(img.bits_per_pixel),
			&(img.line_length), &(img.endian));

	int length = 500;	

	t_point start;
	t_point end;

	start.x = 100;
	start.y = 700;

	end.x =start.x + length;
	end.y = 700;
	draw_hline(&img, start, end);
	t_point mid;
	t_point mid_pt;

	mid_pt.x = (start.x + end.x) / 2;
	mid_pt.y = (start.y + end.y) / 2;
	mid.x = (start.x + end.x) / 2;
	mid.y = start.y - (pow(3, 0.5) * length / 2);

	draw_line(&img, &start, &mid);
	draw_line(&img, &end, &mid);
	// int m = start.x - 1;
	// int n = start.y - 1;
	// while (++m <= mid.x)
	// 	my_mlx_pixel_put(&img, m, n--, 0x00FF0000);
	// m = end.x + 1;
	// n = start.y - 1;
	// while (--m >= mid.x)
	// 	my_mlx_pixel_put(&img, m, n--, 0x00FF0000);
	int k = length;

	while (k < length)
	{
		int j = 0;
		while (j + start.x)
		{
			j++;
		}
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}