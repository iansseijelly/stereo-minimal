// disparity_source.c
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "disparity_source.h"

void compute_disparity(
    unsigned char *left, unsigned char *right, signed char *disparity, 
    int height, int width, int min_disparity, int max_disparity, int half_block_size
) {
    int SAD = 0;
    int min_SAD = INT32_MAX;
    int l_r, l_c, r_r, r_c;

    for (int i = 0 + half_block_size; i < height - half_block_size; i++) {
        for (int j = 0 + half_block_size - min_disparity; j < width - half_block_size - max_disparity; j++) {
            min_SAD = INT32_MAX;
            for (int offset = min_disparity; offset < max_disparity; offset++) {
                SAD = 0;
                for (l_r = i - half_block_size; l_r < half_block_size + i; l_r++) {
                    for (l_c = j - half_block_size; l_c < half_block_size + j; l_c++) {
                        r_r = l_r;
                        r_c = l_c + offset;
                        SAD += abs(left[l_r * width + l_c] - right[r_r * width + r_c]);
                    }
                }
                if (SAD < min_SAD) {
                    min_SAD = SAD;
                    disparity[i * width + j + max_disparity] = offset;
                }
            }
        }
    }
}
