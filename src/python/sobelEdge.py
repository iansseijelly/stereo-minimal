import cv2
import numpy as np
import argparse
import matplotlib.pyplot as plt

def stereoBM_init(numDisparities, blockSize):
    stereo = cv2.StereoBM_create(numDisparities=numDisparities, blockSize=blockSize)
    return stereo

# simple arguments parser
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Simple stereo matching example.')
    parser.add_argument('--left', type=str, help='left image file', required=True)
    args = parser.parse_args()

    # read images as grayscale
    img = cv2.imread(args.left)

    # create stereo matcher with parameters
    gray_left = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY, img)

    grad_x = cv2.Sobel(img, cv2.CV_64F, 1, 0)
    grad_y = cv2.Sobel(img, cv2.CV_64F, 0, 1)

    cv2.imwrite('output/img/grad_x.png', grad_x)
    cv2.imwrite('output/img/grad_y.png', grad_y)

    grad = np.sqrt(grad_x**2 + grad_y**2)
    grad_norm = (grad * 255 / grad.max()).astype(np.uint8)

    print(grad_norm.shape)
    # print the max, min, and mean of the edges
    # print(f"Max: {np.max(edges)}, Min: {np.min(edges)}, Mean: {np.mean(edges)}")
    # generate a distribution of the values
    # plt.hist(edges.ravel(), 256, [0, 256])
    # save the histogram
    # plt.savefig('output/img/python_histogram.png')

    # normalize output
    # edges = cv2.normalize(edges, edges, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)
    # edges = cv2.applyColorMap(edges, cv2.COLORMAP_JET)
    # print the max, min, and mean of the edges
    # print(f"Max: {np.max(edges)}, Min: {np.min(edges)}, Mean: {np.mean(edges)}")
    # show result
    # cv2.imshow('edges', edges)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    #save output
    cv2.imwrite('output/img/edgesSobel.png', grad_norm)
