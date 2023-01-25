#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	printf("%lf\n", atof(av[1]));
}

int get_rgb(int h, int s, int v)
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
	return (r << 16 | g << 8 | b);
}




/*
y = 900
x = 1600


800, 600, 900
*/

	// rng->min_x = transpose(rng->mpx, rng->min_x, i);
	// rng->max_x = transpose(rng->mpx, rng->max_x, i);
	// rng->min_y = transpose(rng->mpy, rng->min_y, i);
	// rng->max_y = transpose(rng->mpy, rng->max_y, i);


	double	transpose(double x, double y, double i)
{
	return (x + ((y - x)) * i);
}