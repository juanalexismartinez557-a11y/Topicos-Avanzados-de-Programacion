#ifndef IMAGENES_H
#define IMAGENES_H

#include <opencv2/opencv.hpp>

using namespace cv;

// Prototipos
void datosImagen(const Mat& img);
Mat resizeImagen(const Mat& img);
void editar(Mat& img);

#endif