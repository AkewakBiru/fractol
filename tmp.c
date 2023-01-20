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