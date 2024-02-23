#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    unsigned char *data;
} Image;

Image *load_image(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("Error: Could not open file for reading\n");
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    printf("File size: %ld\n", file_size);
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

    image->width = 1920; // Set your image width here
    image->height = 1080; // Set your image height here

    // Set the image data pointer
    image->data = data;

    return image;
}

void free_image(Image *image) {
    if (image) {
        free(image->data);
        free(image);
    }
}

int main() {
    const char *file_path = "../../output/intermediate/left";
    Image *image = load_image(file_path);
    if (!image) {
        return 1;
    }

    // Access the image data using image->data
    // Example: Accessing pixel at row 0, column 0, and channel 0 (R) 
    int row = 1080-1, col = 1920-1;
    unsigned char pixel_value = image->data[row*image->width+col];
    printf("Pixel value last: %x\n", pixel_value);

    free_image(image);
    return 0;
}
