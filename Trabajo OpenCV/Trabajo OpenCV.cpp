#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// declaraciones de las funciones que usare
void datosImagen(const Mat& img);
Mat resizeImagen(const Mat& img);
void editar(Mat& img);
void camaraGrises();

void datosImagen(const Mat& img) // funcion para mostrar los datos de la imagen
{
    cout << "Ancho: " << img.cols << endl;
    cout << "Alto : " << img.rows << endl;
    cout << "Canales: " << img.channels() << endl;
}

Mat resizeImagen(const Mat& img) // funcion para redimensionar la imagen
{
    Mat img_resized;
    resize(img, img_resized, Size(1024, 1024));

    imshow("Imagen Original", img);
    imshow("Imagen Redimensionada", img_resized);

    return img_resized;
}

void editar(Mat& img) // funcion para poner un circulo, un rectangulo y un texto
{
    rectangle(img, Point(0,0), Point(img.cols-1, img.rows-1), // rectangulo
              Scalar(0,0,255), 3);

    Point centro(img.cols / 2, img.rows / 2); // circulo
    circle(img, centro, 50, Scalar(0,255,0), 3);

	int baseline = 0; // detalles para el texto
    string texto = "Ejercicio 3 del trabajo OpenCV";

    Size textSize = getTextSize(
        texto,
        FONT_HERSHEY_SIMPLEX,
        1.0,
        2,
        &baseline
    );

    // Coordenadas para centrar abajo
    Point textOrg(
        (img.cols - textSize.width) / 2,
        750
    );

    putText( // texto
        img,
        texto,
        textOrg,
        FONT_HERSHEY_SIMPLEX,
        1.0,
        Scalar(255, 255, 255), 
        2
    );

    imshow("Imagen Editada", img);
}
void camaraGrises()// funcion para usar la camara y mostrar 3 ventanas (normal, grises y editada)
{
	VideoCapture cap(0); // abrir la camara

    if (!cap.isOpened()) // seguro por si algo sale ma
    {
        cout << "Error: No se pudo abrir la camara" << endl;
        return;
    }

	Mat frame, frameGray, frameEdit; // crear matrices para los frames

    // Crear ventanas  que usare
    namedWindow("Camara - Color");
    namedWindow("Camara - Grises");
    namedWindow("Camara - Editada");

    // Acomodo las ventanas, para que no se encimen entre si 
    moveWindow("Camara - Color", 0, 0);
    moveWindow("Camara - Grises", 500, 0);
    moveWindow("Camara - Editada", 1000, 0);

    int i = 0;
    while (true)
    {
		
        cap >> frame;

        if (frame.empty())
            break;

        // Redimensionar para que quepan bien
        resize(frame, frame, Size(490, 300));

        // Ventana 1: normal
        imshow("Camara - Color", frame);

        // Ventana 2: gris
        cvtColor(frame, frameGray, COLOR_BGR2GRAY);
        imshow("Camara - Grises", frameGray);

        // Ventana 3: editada
        frameEdit = frame.clone();

        // Rectangulo rojo
        rectangle(frameEdit,
            Point(0, 0),
            Point(frameEdit.cols - 1, frameEdit.rows - 1),
            Scalar(0, 0, 255), 3);

        // Circulo verde
        Point centro(frameEdit.cols / 2, frameEdit.rows / 2);
        circle(frameEdit, centro, 50, Scalar(0, 255, 0), 3);

        // Texto
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

        // Borde negro
        putText(frameEdit, texto, textOrg,
            FONT_HERSHEY_SIMPLEX, 0.8,
            Scalar(0, 0, 0), 4);

        // Texto blanco
        putText(frameEdit, texto, textOrg,
            FONT_HERSHEY_SIMPLEX, 0.8,
            Scalar(255, 255, 255), 2);

        imshow("Camara - Editada", frameEdit);

        if (waitKey(30) == 27) // ESC
            break;

        if (i < 1) { //Seguro para que no se repita el mensaje
            cout << "Camara activa. Presiona ESC para salir..." << endl; // mensaje para el usuario
            i++;
        }
    }
    cap.release();
    destroyAllWindows();
}


int main()
{
    Mat img = imread("C:/Users/juana/Documents/GitHub/Programacion-Avanzada/Trabajo OpenCV/img/flash.jpg"); // mi imagen

    if (img.empty()) // seguro por si la imagen
    {
        cout << "Error, algo esta mal con la imagen" << endl;
        return -1;
    }

    int opcion;

    Mat img_resized;
    bool salir = true;
    while (salir == true) 
    {
        cout << "Seleccione el ejercicio a ejecutar (1-Datos, 2-Resize, 3-Editar, 4-Usar camara, 5-Salir): ";
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
