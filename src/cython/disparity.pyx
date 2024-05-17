# disparity.pyx
cdef extern from "disparity_source.h":
    void compute_disparity(
        unsigned char *left, unsigned char *right, signed char *disparity,
        int height, int width, int min_disparity, int max_disparity, int half_block_size
    )

import numpy as np
cimport numpy as np

def compute_disparity_py(np.ndarray[np.uint8_t, ndim=2] left,
                         np.ndarray[np.uint8_t, ndim=2] right,
                         int min_disparity, int max_disparity, int half_block_size):
    cdef int height = left.shape[0]
    cdef int width = left.shape[1]
    cdef np.ndarray[np.int8_t, ndim=2] disparity = np.zeros((height, width), dtype=np.int8)
    
    compute_disparity(
        <unsigned char *> left.data, <unsigned char *> right.data,
        <signed char *> disparity.data, height, width,
        min_disparity, max_disparity, half_block_size
    )
    
    return disparity

