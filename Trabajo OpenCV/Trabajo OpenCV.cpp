#include <iostream>
#include <opencv2/opencv.hpp>

#include "imagenes.h"
#include "camara.h"

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("C:/Users/juana/Documents/GitHub/Programacion-Avanzada/Trabajo OpenCV/img/flash.jpg");

    if (img.empty())
    {
        cout << "Error, algo esta mal con la imagen" << endl;
        return -1;
    }

    int opcion;
    Mat img_resized;
    bool salir = true;

    while (salir)
    {
        cout << "Seleccione el ejercicio a ejecutar "
            << "(1-Datos, 2-Resize, 3-Editar, 4-Usar camara, 5-Salir): ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            datosImagen(img);
            break;

        case 2:
            img_resized = resizeImagen(img);
            waitKey(0);
            break;

        case 3:
            img_resized = resizeImagen(img);
            waitKey(0);
            editar(img_resized);
            waitKey(0);
            break;

        case 4:
            camaraGrises();
            waitKey(0);
            break;

        case 5:
            salir = false;
            break;

        default:
            cout << "Ingresa una opcion valida" << endl;
            break;
        }
    }

    destroyAllWindows();
    return 0;
}
