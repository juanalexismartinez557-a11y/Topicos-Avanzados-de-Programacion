#include "camara.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void camaraGrises()
{
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Error: No se pudo abrir la camara" << endl;
        return;
    }

    Mat frame, frameGray, frameEdit;

    namedWindow("Camara - Color");
    namedWindow("Camara - Grises");
    namedWindow("Camara - Editada");

    moveWindow("Camara - Color", 0, 0);
    moveWindow("Camara - Grises", 500, 0);
    moveWindow("Camara - Editada", 1000, 0);

    int i = 0;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        resize(frame, frame, Size(490, 300));

        imshow("Camara - Color", frame);

        cvtColor(frame, frameGray, COLOR_BGR2GRAY);
        imshow("Camara - Grises", frameGray);

        frameEdit = frame.clone();

        rectangle(frameEdit,
            Point(0, 0),
            Point(frameEdit.cols - 1, frameEdit.rows - 1),
            Scalar(0, 0, 255), 3);

        Point centro(frameEdit.cols / 2, frameEdit.rows / 2);
        circle(frameEdit, centro, 50, Scalar(0, 255, 0), 3);

        string texto = "Ejercicio OpenCV - Camara";

        int baseline = 0;
        Size textSize = getTextSize(
            texto,
            FONT_HERSHEY_SIMPLEX,
            0.8,
            2,
            &baseline
        );

        Point textOrg(
            (frameEdit.cols - textSize.width) / 2,
            frameEdit.rows - 20
        );

        putText(frameEdit, texto, textOrg,
            FONT_HERSHEY_SIMPLEX, 0.8,
            Scalar(0, 0, 0), 4);

        putText(frameEdit, texto, textOrg,
            FONT_HERSHEY_SIMPLEX, 0.8,
            Scalar(255, 255, 255), 2);

        imshow("Camara - Editada", frameEdit);

        if (waitKey(30) == 27)
            break;

        if (i < 1)
        {
            cout << "Camara activa. Presiona ESC para salir..." << endl;
            i++;
        }
    }

    cap.release();
    destroyAllWindows();
}
