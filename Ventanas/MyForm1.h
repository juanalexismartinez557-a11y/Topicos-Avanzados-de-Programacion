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
};
