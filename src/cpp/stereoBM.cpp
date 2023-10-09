// A cpp version of stereoBM.py, to be deployed on SoCs
#include <iostream>
#include <opencv2/opencv.hpp>

// similarly, a simple parser
int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: ./stereoBM <left_img> <right_img>" << std::endl;
        return -1;
    }

    // load images
    cv::Mat left_img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat right_img = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

    // stereoBM
    cv::Ptr<cv::StereoBM> stereo = cv::StereoBM::create(16, 15);
    cv::Mat disparity;
    stereo->compute(left_img, right_img, disparity);

    // save disparity
    cv::imwrite("disparity.png", disparity);

    return 0;
}