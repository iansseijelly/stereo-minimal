import numpy as np
from disparity import compute_disparity_py

# Example usage
left_image = np.random.randint(0, 256, (100, 100), dtype=np.uint8)
right_image = np.random.randint(0, 256, (100, 100), dtype=np.uint8)

min_disparity = 0
max_disparity = 64
half_block_size = 5

disparity_map = compute_disparity_py(left_image, right_image, min_disparity, max_disparity, half_block_size)
print(disparity_map)

