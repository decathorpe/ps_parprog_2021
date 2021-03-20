#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
    // rectangle coordinates in the complex plane
    float x_min = -2.5f;
    float x_max =  1.0f;
    float y_min = -1.0f;
    float y_max =  1.0f;

    // run calculations for horizontal lines of pixels in parallel
    #pragma omp parallel for
    for (int j = 0; j < Y; j++) {
        for (int i = 0; i < X; i++) {
            float x = 0.0f;
            float y = 0.0f;

            // transform pixel coordinates into complex coordinates
            float cx = ((float) i * (x_max - x_min) / ((float) X)) + x_min;
            float cy = ((float) j * (y_max - y_min) / ((float) Y)) + y_min;

            int iteration = 0;
            while ((x*x + y*y <= 2*2) && iteration < MAX_ITER) {
                float x_tmp = x*x - y*y + cx;
                y = 2*x*y + cy;
                x = x_tmp;
                iteration++;
            }

            // normalize iteration number to 8-bit grayscale value
            uint8_t norm_iteration =  iteration * 255 / MAX_ITER;
            image[j][i] = norm_iteration;
        }
    }
}

int main() {
	uint8_t image[Y][X];

    double start_time = omp_get_wtime();

	calc_mandelbrot(image);

    double end_time = omp_get_wtime();

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);

    printf("time: %2.5f seconds\n", end_time - start_time);

	return EXIT_SUCCESS;
}
