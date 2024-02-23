# A utility script reading computed images and display them via OpenCV 
import cv2
import numpy as np

# simple arguments parser
if __name__ == '__main__':

    # read raw disparity map bytes
    with open('output/intermediate/disparity', 'rb') as f:
        raw_disp = f.read()
    # convert to numpy array
    disp = np.frombuffer(raw_disp, dtype=np.uint8)
    # reshape to original shape
    disp = disp.reshape(1080, 1920)
    # check for any non-zero values
    # create a greyscale image from the numpy array
    disparity_normalized = cv2.normalize(disp, None, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)
    print(np.count_nonzero(disparity_normalized))
    disparity_normalized = cv2.applyColorMap(disparity_normalized, cv2.COLORMAP_JET)
    # store the image
    cv2.imwrite('output/img/c_disparity.png', disp)
