#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

class ImageProcessor
{
public:
    static Mat loadImage(const std::string& path);
    static Mat toGray(const Mat& img);
    static Mat thresholdWB(const Mat& img);
    static Mat thresholdBW(const Mat& img);
    static Mat sobel(const Mat& img);
    static Mat canny(const Mat& img);
    static Mat rotate(const Mat& img);
    static Mat zoom(const Mat& img);
};
