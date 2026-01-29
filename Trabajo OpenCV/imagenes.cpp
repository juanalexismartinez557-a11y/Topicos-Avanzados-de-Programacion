#include "imagenes.h"
#include <iostream>

using namespace std;

void datosImagen(const Mat& img)
{
    cout << "Ancho: " << img.cols << endl;
    cout << "Alto : " << img.rows << endl;
    cout << "Canales: " << img.channels() << endl;
}

Mat resizeImagen(const Mat& img)
{
    Mat img_resized;
    resize(img, img_resized, Size(1024, 1024));

    imshow("Imagen Original", img);
    imshow("Imagen Redimensionada", img_resized);

    return img_resized;
}

void editar(Mat& img)
{
    rectangle(img, Point(0, 0),
        Point(img.cols - 1, img.rows - 1),
        Scalar(0, 0, 255), 3);

    Point centro(img.cols / 2, img.rows / 2);
    circle(img, centro, 50, Scalar(0, 255, 0), 3);

    int baseline = 0;
    string texto = "Ejercicio 3 del trabajo OpenCV";

    Size textSize = getTextSize(
        texto,
        FONT_HERSHEY_SIMPLEX,
        1.0,
        2,
        &baseline
    );

    Point textOrg(
        (img.cols - textSize.width) / 2,
        750
    );

    putText(
        img,
        texto,
        textOrg,
        FONT_HERSHEY_SIMPLEX,
        1.0,
        Scalar(255, 255, 255),
        2
    );

    imshow("Imagen Editada", img);
    waitKey(0);
    destroyAllWindows();
}
