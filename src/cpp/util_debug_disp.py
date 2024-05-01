# A utility script reading computed images and display them via OpenCV 
import cv2
import numpy as np
import matplotlib.pyplot as plt

# simple arguments parser
if __name__ == '__main__':

    # read raw disparity map bytes
    with open('output/intermediate/disparity', 'rb') as f:
        raw_disp = f.read()
    with open('output/intermediate/dimensions', 'r') as f:
        dimensions = f.read()
        # print(dimensions)
        height, width = dimensions.split(',')
    # convert to numpy array
    disp = np.frombuffer(raw_disp, dtype=np.int8)
    # reshape to original shape
    disp = disp.reshape(int(height), int(width))
    print(f"max: {np.max(disp)}, min: {np.min(disp)}, mean: {np.mean(disp)}")
    # generate a distribution of the values
    plt.hist(disp.ravel())
    # save the histogram
    plt.savefig('output/img/c_histogram.png')
    # create a greyscale image from the numpy array
    disparity_normalized = cv2.normalize(disp, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)
    disparity_normalized = cv2.applyColorMap(disparity_normalized, cv2.COLORMAP_JET)
    # store the image
    cv2.imwrite('output/img/c_disparity.png', disparity_normalized)

    raw_disp = disp.tobytes()

    # convert raw data to byte-by-byte, human-readable format
    with open('output/intermediate/dis_hex.txt', 'w') as f:
        for i in range(256):
            for j in range(256):
                f.write(f"{raw_disp[i*256+j]:02X} ")
            f.write("\n")