# A utility script reading images via OpenCV and storing them in intermediate forms for actual compute

import cv2
import numpy as np
import argparse

# simple arguments parser
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Simple stereo matching example.')
    parser.add_argument('--left', type=str, help='left image file', required=True)
    parser.add_argument('--right', type=str, help='right image file', required=True)
    args = parser.parse_args()

    # read images as grayscale
    imgL = cv2.imread(args.left)
    imgR = cv2.imread(args.right)

    gray_left = cv2.cvtColor(imgL, cv2.COLOR_BGR2GRAY, imgL)
    gray_right = cv2.cvtColor(imgR, cv2.COLOR_BGR2GRAY, imgR)

    # resize to 256*256
    gray_left = cv2.resize(gray_left, (256, 256))
    gray_right = cv2.resize(gray_right, (256, 256))

    raw_left = gray_left.tobytes()
    #print the last 10 bytes
    # print(raw_left[-10:])
    height, width = gray_left.shape
    print(f"Height: {height}, Width: {width}")
    raw_right = gray_right.tobytes()

    # write to files
    with open('output/intermediate/left', 'wb') as f:
        f.write(raw_left)
    with open('output/intermediate/right', 'wb') as f:
        f.write(raw_right)
    with open('output/intermediate/dimensions', 'w') as f:
        f.write(f"{height},{width}")
    
    # convert raw data to byte-by-byte, human-readable format
    with open('output/intermediate/left_hex.txt', 'w') as f:
        for i in range(256):
            for j in range(256):
                f.write(f"{raw_left[i*256+j]:02X} ")
            f.write("\n")
    
    with open('output/intermediate/right_hex.txt', 'w') as f:
        for i in range(256):
            for j in range(256):
                f.write(f"{raw_right[i*256+j]:02X} ")
            f.write("\n")
        