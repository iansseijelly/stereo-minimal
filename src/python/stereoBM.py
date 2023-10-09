import cv2
import numpy as np
import argparse

def stereoBM_init(numDisparities, blockSize):
    stereo = cv2.StereoBM_create(numDisparities=numDisparities, blockSize=blockSize)
    return stereo

# simple arguments parser
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Simple stereo matching example.')
    parser.add_argument('--left', type=str, help='left image file', required=True)
    parser.add_argument('--right', type=str, help='right image file', required=True)
    parser.add_argument('--num-disparity', type=int, help='disparity', default=128)
    parser.add_argument('--block-size', type=int, help='block size', default=9)
    args = parser.parse_args()

    block_size = args.block_size
    if block_size % 2 == 0:
        block_size += 1

    # read images as grayscale
    imgL = cv2.imread(args.left)
    # cv2.imshow('left', imgL)
    # cv2.waitKey(0)  # Wait indefinitely until a key is pressed
    # cv2.destroyAllWindows()  # Close all OpenCV windows
    imgR = cv2.imread(args.right)

    # create stereo matcher with parameters
    stereo = stereoBM_init(args.num_disparity, block_size)

    gray_left = cv2.cvtColor(imgL, cv2.COLOR_BGR2GRAY, imgL)
    gray_right = cv2.cvtColor(imgR, cv2.COLOR_BGR2GRAY, imgR)

    # compute disparity
    disparity = stereo.compute(gray_left, gray_right)

    # normalize output
    disparity = cv2.normalize(disparity, disparity, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8U)

    # show result
    cv2.imshow('disparity', disparity)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    #save output
    cv2.imwrite('output/img/disparityBM.png', disparity)
