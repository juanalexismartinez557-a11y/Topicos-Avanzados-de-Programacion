#pragma once

#include <opencv2/opencv.hpp>
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

public ref class MyForm1 : public Form
{
public:
    MyForm1(void);
protected:
    ~MyForm1();

private:
    // Frames
    cv::Mat* originalFrame;
    cv::Mat* processedFrame;
    cv::Mat ApplyFilters(cv::Mat input);


    // Tipo de filtro activo
    enum class FilterType
    {
        None,
        Grayscale,
        ThresholdBW,
        ThresholdWB,
        Canny,
        Sobel,
        RGBSplit
    };

    FilterType currentFilter;
    PictureBox^ pictureBox;
    Button^ btnLoadImage;
    Button^ btnStartCamera;
    Button^ btnStopCamera;
    Timer^ timer;

    // IMPORTANTE: usar punteros
    cv::VideoCapture* cap;
    cv::Mat* frame;
    void ClearDisplay();
    void InitializeComponent(void);
    void BtnLoadImage_Click(Object^ sender, EventArgs^ e);
    void BtnStartCamera_Click(Object^ sender, EventArgs^ e);
    void BtnStopCamera_Click(Object^ sender, EventArgs^ e);
    void Timer_Tick(Object^ sender, EventArgs^ e);

    Bitmap^ MatToBitmap(cv::Mat& mat);

    // Botones filtros
    System::Windows::Forms::Button^ btnGray;
    System::Windows::Forms::Button^ btnBinary;
    System::Windows::Forms::Button^ btnBinaryInv;
    System::Windows::Forms::Button^ btnCanny;
    System::Windows::Forms::Button^ btnSobel;
    System::Windows::Forms::Button^ btnRGB;
    System::Windows::Forms::Button^ btnReset;

    // TrackBars
    System::Windows::Forms::TrackBar^ trackBarThreshold;
    System::Windows::Forms::TrackBar^ trackBarCanny;
    System::Windows::Forms::TrackBar^ trackBarZoom;

    // Eventos
    System::Void BtnGray_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void BtnBinary_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void BtnBinaryInv_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void BtnCanny_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void BtnSobel_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void BtnRGB_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void BtnReset_Click(System::Object^ sender, System::EventArgs^ e);

    System::Void TrackBarThreshold_Scroll(System::Object^ sender, System::EventArgs^ e);
    System::Void TrackBarCanny_Scroll(System::Object^ sender, System::EventArgs^ e);
    System::Void TrackBarZoom_Scroll(System::Object^ sender, System::EventArgs^ e);

    Label^ lblThreshold;
    Label^ lblCanny;
    Label^ lblZoom;
};
