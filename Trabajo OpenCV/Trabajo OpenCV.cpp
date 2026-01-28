#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // Cargar imagen en color
    Mat img = imread("C:/Users/juana/Documents/GitHub/Programacion-Avanzada/Trabajo OpenCV/img/flash.jpg");

    // Verificar carga
    if (img.empty())
    {
        cout << "No se pudo abrir la imagen" << endl;
        return -1;
    }

    // Redimensionar
    Mat img_resized;
    resize(img, img_resized, Size(636, 316));

    // Convertir a escala de grises
    Mat img_gray;
    cvtColor(img_resized, img_gray, COLOR_BGR2GRAY);

    // Mostrar resultados
    imshow("Imagen Original", img);
    imshow("Imagen Redimensionada", img_resized);
    imshow("Imagen Escala de Grises", img_gray);

    waitKey(0);
    return 0;
}