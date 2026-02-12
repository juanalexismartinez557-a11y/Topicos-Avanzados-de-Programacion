#include "ImageProcessor.h"

Mat ImageProcessor::loadImage(const std::string& path)
{
    return imread(path);
}

Mat ImageProcessor::toGray(const Mat& img)
{
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    return gray;
}

Mat ImageProcessor::thresholdWB(const Mat& img)
{
    Mat gray, bin;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    threshold(gray, bin, 128, 255, THRESH_BINARY);
    return bin;
}

Mat ImageProcessor::thresholdBW(const Mat& img)
{
    Mat gray, bin;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    threshold(gray, bin, 128, 255, THRESH_BINARY_INV);
    return bin;
}

Mat ImageProcessor::sobel(const Mat& img)
{
    Mat gray, grad;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Sobel(gray, grad, CV_8U, 1, 1);
    return grad;
}

Mat ImageProcessor::canny(const Mat& img)
{
    Mat gray, edges;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    Canny(gray, edges, 100, 200);
    return edges;
}

Mat ImageProcessor::rotate(const Mat& img)
{
    Mat rotated;
    cv::rotate(img, rotated, ROTATE_90_CLOCKWISE);
    return rotated;
}

Mat ImageProcessor::zoom(const Mat& img)
{
    Mat zoomed;
    resize(img, zoomed, Size(), 1.5, 1.5);
    return zoomed;
}
