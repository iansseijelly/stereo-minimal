// This code is adapted from the following source:
// https://github.com/ankitdhall/stereo-block-matching/blob/master/sbm.cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

typedef struct {
    int width;
    int height;
    signed char *data;
} Disp_Image;

void free_image(Image *image) {
    if (image) {
        free(image->data);
        free(image);
    }
}

void free_disp_image(Disp_Image *image) {
    if (image) {
        free(image->data);
        free(image);
    }
}

Image *load_image(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("Error: Could not open file for reading\n");
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the image data
    unsigned char *data = (unsigned char *)malloc(file_size);
    if (!data) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Read the data from the file
    size_t bytes_read = fread(data, 1, file_size, file);
    if (bytes_read != file_size) {
        printf("Error: Could not read file\n");
        fclose(file);
        free(data);
        return NULL;
    }

    fclose(file);

    // Create an Image structure and populate its fields
    Image *image = (Image *)malloc(sizeof(Image));
    if (!image) {
        printf("Error: Memory allocation failed\n");
        free(data);
        return NULL;
    }

    FILE *dim_file = fopen("../../output/intermediate/dimensions", "r");
    if (!dim_file) {
        printf("Error: Could not open file for writing\n");
        free_image(image);
        return NULL;
    }
    if (fscanf(dim_file, "%d,%d", &image->height, &image->width) != 2) {
        printf("Error: Failed to read dimensions from file\n");
        fclose(file);
        return NULL;
    }
    // Set the image data pointer
    image->data = data;

    return image;
}


int square(char x) {
    return (int)x*(int)x;
}

// Sobel kernels for horizontal and vertical edge detection
const int8_t sobel_horizontal[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
const int8_t sobel_vertical[3][3] = {
    { 1,  2,  1},
    { 0,  0,  0},
    {-1, -2, -1}
};


Image* compute_sobel_edge_detection(Image *image) {
    // Iterate over each pixel in the image
    int WIDTH = image->width;
    int HEIGHT = image->height;
    int32_t gradient_x[HEIGHT][WIDTH];
    int32_t gradient_y[HEIGHT][WIDTH];
    for (int y = 1; y < HEIGHT - 1; y++) {
        for (int x = 1; x < WIDTH - 1; x++) {
            int32_t sum_x = 0;
            int32_t sum_y = 0;
            // Apply the Sobel kernels to the neighborhood of the current pixel
            for (int ky = 0; ky < 3; ky++) {
                for (int kx = 0; kx < 3; kx++) {
                    int px = x + kx - 1;
                    int py = y + ky - 1;
                    // Accumulate the weighted sum for horizontal and vertical gradients
                    sum_x += image->data[py*WIDTH+px] * sobel_horizontal[ky][kx];
                    sum_y += image->data[py*WIDTH+px] * sobel_vertical[ky][kx];
                }
            }
            // Store the gradients in the temporary buffers
            gradient_x[y][x] = sum_x;
            gradient_y[y][x] = sum_y;
        }
    }

    signed char *edge_map = (signed char *)malloc(WIDTH*HEIGHT);
    if (!edge_map) {
        printf("Error: Memory allocation failed\n");
        return NULL;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Calculate the magnitude of the gradient at each pixel
            int16_t gx = gradient_x[y][x];
            int16_t gy = gradient_y[y][x];
            int16_t magnitude = (gx * gx + gy * gy);
            // Clamp the magnitude to [0, 255]
            magnitude = magnitude > square(0) ? 255 : 0;
            // Store the magnitude in the edge map
            edge_map[y*WIDTH+x] = magnitude;
        }
    }

    Image *edge_image = (Image *)malloc(sizeof(Image));
    if (!edge_image) {
        printf("Error: Memory allocation failed\n");
        free(edge_map);
        return NULL;
    }
    edge_image->width = WIDTH;
    edge_image->height = HEIGHT;
    edge_image->data = edge_map;
    return edge_image;
}

int main() {
    const char *left_file_path = "../../output/intermediate/left";
    Image *left_image = load_image(left_file_path);
    if (!left_image) {
        return 1;
    }
    Image *edge_image = compute_sobel_edge_detection(left_image);
    // Save the disparity image
    FILE *file = fopen("../../output/intermediate/disparity", "wb");
    if (!file) {
        printf("Error: Could not open file for writing\n");
        free_image(left_image);
        free_disp_image(edge_image);
        return 1;
    }
    // write only the data
    fwrite(edge_image->data, 1, edge_image->width*edge_image->height, file);
    fclose(file);
    free_image(left_image);
    free_image(edge_image);
    return 0;
}
