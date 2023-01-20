import numpy as np
import matplotlib.pyplot as plt

def mandelbrot(c):
    z = c
    n = 256
    for i in range(n):
        if abs(z) > 2:
            return i
        z = z*z + c
    return n

def mandelbrot_set(xmin, xmax, ymin, ymax, width, height, max_iter):
    r1 = np.linspace(xmin, xmax, width)
    r2 = np.linspace(ymin, ymax, height)
    n3 = np.empty((width,height))
    for i in range(width):
        for j in range(height):
            n3[i,j] = mandelbrot(r1[i] + 1j*r2[j])
    return (r1, r2, n3)

def plot_mandelbrot(xmin, xmax, ymin, ymax, width=10, height=10):
    plt.figure(figsize=(width, height))
    x, y, z = mandelbrot_set(xmin, xmax, ymin, ymax, width*100, height*100, 256)
    plt.imshow(z.T, extent=[xmin, xmax, ymin, ymax], cmap='nipy_spectral',
               origin='lower', interpolation='bicubic')
    plt.colorbar()
    plt.show()

plot_mandelbrot(-2, 0.5, -1.25, 1.25)
