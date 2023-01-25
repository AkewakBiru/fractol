#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITERATIONS 1000

int main() {
double min_x = -2;
double max_x = 1;
double min_y = -1;
double max_y = 1;
double x_step = (max_x - min_x) / WIDTH;
double y_step = (max_y - min_y) / HEIGHT;
srand(time(NULL)); // seed the random number generator

for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
        double c_real = min_x + x * x_step;
        double c_imag = max_y - y * y_step;
        double complex c = c_real + c_imag * I;
        double complex z = 0;

        int iterations = 0;
        while (cabs(z) < 2 && iterations < MAX_ITERATIONS) {
            z = z * z + c;
            iterations++;
        }

        if (iterations == MAX_ITERATIONS) {
            printf("*");
        } else {
            double color_scale = (double)iterations / MAX_ITERATIONS;
            int red = (int)(sin(color_scale * 3.14) * 255);
            int green = (int)(sin(color_scale * 3.14 * 2) * 255);
            int blue = (int)(sin(color_scale * 3.14 * 3) * 255);
            printf("\033[48;2;%d;%d;%dm ", red, green, blue);
        }
    }
    printf("\n");
}

return 0;
}

void	renderer(t_vars vars, t_frame *frame, t_data img)
{
	int SCALE = 200.0;
	int num_iter_per_pixel[200];
	int iter_count[WIDTH][HEIGHT];
	int max_iter = 200;
	float hue[WIDTH][HEIGHT];

	double x0 = -0.90;
	double x = 0.0;
	double y = 0.0;
	double y0 = 0.00;
	int iteration = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			iteration = 0;
			while (x * x + y * y <= (1 << 16) && iteration < max_iter)
			{
				double x_temp = x * x - y * y + x0;
				y = 2 * x * y + y0;
				x = x_temp;
				iteration++;
			}
			if (iteration < max_iter)
			{
				double log_zn = log(x * x + y * y) / 2;
				double nu = log(log_zn / log(2)) / log(2);
				iteration = iteration + 1 - nu;
			}
			iter_count[i][j] = iteration;
		}
	}
	// for (int i = 0; i<WIDTH; i++)
	// {
	// 	for (int y = 0; y <HEIGHT; y++)
	// 	{
	// 		int k = iter_count[i][y];
	// 		num_iter_per_pixel[k]++;
	// 		// int color = hue_to_rgb(hue[i][y]);
	// 		// int color = escape((i - (WIDTH / 2.0)) / SCALE, (y - (HEIGHT / 2.0)) / SCALE);
	// 		// my_mlx_pixel_put(&img, i, y, color);
	// 	}
	// }
	// int total = 0;
	// for (int c = 0; c < max_iter; c++)
	// 	total += num_iter_per_pixel[c];
	// for (int i = 0; i < WIDTH; i++)
	// {
	// 	for (int j = 0; j < HEIGHT; j++)
	// 		hue[i][j] = 0.0;
	// }
	// for (int a = 0; a < WIDTH; a++)
	// {
	// 	for (int b = 0; b < HEIGHT; b++)
	// 	{
	// 		int iteration = iter_count[a][b];
	// 		for (int k = 0; k <= iteration; k++)
	// 			hue[a][b] += num_iter_per_pixel[k] / total;
	// 	}
	// }
	// for (int i = 0; i<WIDTH; i++)
	// {
	// 	for (int y = 0; y <HEIGHT; y++)
	// 	{
	// 		if (hue[i][y] < 0)
	// 			hue[i][y] = -hue[i][y];
	// 		my_mlx_pixel_put(&img, i, y, ((int)hue[i][y] << 16 | (int) hue[i][y] << 8 | (int)hue[i][y]));
	// 	}
	// }
}


int hsb_to_rgb(int h, int s, int v)
{
	int M = 255 * v;
	int m = M * (1 - s);
	int z = (M - m) * (1 - abs((h / 60) % 2 - 1));
	int r, g, b;
	if (0 <= h && h < 60)
	{
		r = M;
		g = z + m;
		b = m;
	}
	else if (60 <= h && h < 120)
	{
		r = z + m;
		g = M;
		b = m;
	}
	else if (120 <= h && h < 180)
	{
		r = m;
		g = M;
		b = z + m;
	}
	else if (180 <= h && h < 240)
	{
		r = m;
		g = z + m;
		b = M;
	}
	else if (240 <= h && h < 300)
	{
		r = z + m;
		g = m;
		b = M;
	}
	else if (300 <= h && h < 360)
	{
		r = M;
		g = m;
		b = z + m;
	}
	return (r >> 16 | g >> 8 | b);
}

	// cl.channels[0] = (unsigned int)(sin(0.016 * index + 10) * 230 + 255);
		// cl.channels[1] = (unsigned int)(sin(0.013 * index + 5) * 230 + 255);
		// cl.channels[2] = (unsigned int)(sin(0.01 * index + 1) * 230 + 255);
		// // cl.channels[3] = (unsigned char)1 + (int)rng->color | (int)log(iter);
		// cl.channels[3] = 0xFFFFFFFF & rng->color;

 		// cl.channels[0] = palette[(int)(sin(0.016 * index + 10) * 230 + 255) % 5];
		// cl.channels[1] = palette[(int)(sin(0.013 * index + 5) * 230 + 255) % 5];
		// cl.channels[2] = palette[(int)(sin(0.01 * index + 1) * 230 + 255) % 5];
		// cl.channels[3] = 0xFFFFFFFF & rng->color;


		// v = pow(pow((iter / rng->max_iter), 2) * 4, 1.5);
		// my_mlx_pixel_put(&(rng->img), x, y, (int)powf(((double)iter / rng->max_iter) * 360, 1.5) % 360);
		// my_mlx_pixel_put(&(rng->img), x, y, (int)log(iter / rng->max_iter) * iter << 16 | iter);
		// my_mlx_pixel_put(&(rng->img), x+1, y, (int)powf(((double)iter / rng->max_iter) * 360, 1.5) % 360 >> (iter * iter));
		// my_mlx_pixel_put(&(rng->img), 1, y+1, (int)powf(((double)iter / rng->max_iter) * 360, 1.5) % 360 | (iter * iter * iter));
		// my_mlx_pixel_put(&(rng->img), x, y, (pow(cos(iter * 3.14 + 3.14) + 1, iter) / 2 * 255));

			// my_mlx_pixel_put(&(rng->img), x, y, (char)(15 * (1 - t) * pow(t, 3) * 255) & 0x00FF00FF);
		// my_mlx_pixel_put(&(rng->img), x, y, (double)iter + 2 - log(log(z.re* z.re + z.im * z.im)) / log(2));
	// my_mlx_pixel_put(&(rng->img), x, y, (char)(pow(t, 0.5) * 255) << 16);


void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst++ = color.channels[3];
	*(unsigned int *)dst++ = color.channels[2];
	*(unsigned int *)dst++ = color.channels[1];
	*(unsigned int *)dst++ = color.channels[0];
}

// int palette[5] = {
// 					(0 << 16 | 7 << 8 | 100), (32 << 16 | 107 << 8 | 203), (237 << 16 | 255 << 8 | 255)
// 					, (255 << 16 | 170 << 8 | 0), (0 << 16 | 2 << 8 | 0)};

// int palette[5] = {
// 	((0 << 24) | (255)), ((25 << 24) | (192)), ((50 << 24) | (128)), ((75 << 24) | (64)), ((100 << 24) | (0))
// };

int palette[5] = {0x000000FF, 0x0000FFFF, 0x0000FF00, 0x0000FFFF, 0x00FF0000};

typedef struct s_color
{
	unsigned int channels[4];
} t_color;


int	get_color(int iter, t_rng *rng)
{
	if (iter == rng->max_iter)
		return (palette[((iter * 2) << 16) % 5]);
		// return (0);
	else if (iter < 64)
		return (iter * 2 << 8 | (iter / rng->max_iter) * 255);
	else if (iter < 128)
		return ((((iter - 64) * 128) / 126 + 128) << 12);
	else if (iter < 256)
		return ((((iter - 128) * 62) / 127 + 193) << 16);
}

	// t_color cl;
	// double t = (double)iter / rng->max_iter;
	// double index = iter + 1 - log((log(pow(pow(z.re, 2) + pow(z.im, 2), 2))) / log(2)) / log(2);
		// cl = (t_color){0, 0, 0, 0};


		// my_mlx_pixel_put(&(rng->img), x, y, palette[iter % 5] << 10);
		// my_mlx_pixel_put(&(rng->img), x, y, get_rgb(iter % 256 / 255, 100, (iter / rng->max_iter) * 100));
	// else
		// my_mlx_pixel_put(&(rng->img), x, y, (0x610000 << 24 | 0x377D14 << 8 | 0x000033) << iter);
		// my_mlx_pixel_put(&(rng->img), x, y, get_rgb(iter % 256 / 255, 1, 1));
// my_mlx_pixel_put(&(rng->img), x, y, (((((int)(log(iter)) | iter) << iter)) << 8 | ((((int)(log(iter)) | iter) << iter)) << 8 | ((((int)(log(iter)) | palette[iter % 5]) << iter)) << 8));
		// my_mlx_pixel_put(&(rng->img), x, y, get_rgb(iter % 256 / 255, 1, 0));
		// my_mlx_pixel_put(&(rng->img), x, y, (((((int)(log(iter)) | iter) << (iter << 2)))));
		// my_mlx_pixel_put(&(rng->img), x, y, 9 * (1 - iter / rng->max_iter) * pow(iter / rng->max_iter, 3) * 255);
		// my_mlx_pixel_put(&(rng->img), x, y, 0x160C1D);