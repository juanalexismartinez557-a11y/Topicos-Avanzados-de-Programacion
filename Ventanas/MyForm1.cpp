#include "MyForm1.h"

MyForm1::MyForm1(void)
{
    InitializeComponent();
    cap = new cv::VideoCapture();
    frame = new cv::Mat();
}

MyForm1::~MyForm1()
{
    if (cap->isOpened())
        cap->release();

    delete cap;
    delete frame;
}

void MyForm1::InitializeComponent(void)
{
    this->Width = 900;
    this->Height = 600;
    this->Text = "OpenCV - Imagen y Camara";

    pictureBox = gcnew PictureBox();
    pictureBox->Dock = DockStyle::Fill;
    pictureBox->SizeMode = PictureBoxSizeMode::Zoom;

    btnLoadImage = gcnew Button();
    btnLoadImage->Text = "Cargar Imagen";
    btnLoadImage->Dock = DockStyle::Top;
    btnLoadImage->Click += gcnew EventHandler(this, &MyForm1::BtnLoadImage_Click);

    btnStartCamera = gcnew Button();
    btnStartCamera->Text = "Iniciar Camara";
    btnStartCamera->Dock = DockStyle::Top;
    btnStartCamera->Click += gcnew EventHandler(this, &MyForm1::BtnStartCamera_Click);

    btnStopCamera = gcnew Button();
    btnStopCamera->Text = "Detener Camara";
    btnStopCamera->Dock = DockStyle::Top;
    btnStopCamera->Click += gcnew EventHandler(this, &MyForm1::BtnStopCamera_Click);

    timer = gcnew Timer();
    timer->Interval = 30;
    timer->Tick += gcnew EventHandler(this, &MyForm1::Timer_Tick);

    this->Controls->Add(pictureBox);
    this->Controls->Add(btnStopCamera);
    this->Controls->Add(btnStartCamera);
    this->Controls->Add(btnLoadImage);
}

void MyForm1::ClearDisplay()
{
    timer->Stop();

    if (cap->isOpened())
        cap->release();

    if (pictureBox->Image != nullptr)
    {
        delete pictureBox->Image;
        pictureBox->Image = nullptr;
    }
}


void MyForm1::BtnLoadImage_Click(Object^ sender, EventArgs^ e)
{
    ClearDisplay();

    if (!cap->open(0))
    {
        MessageBox::Show("No se pudo abrir la cámara");
        return;
    }

    timer->Start();

    timer->Stop();

    OpenFileDialog^ dialog = gcnew OpenFileDialog();
    dialog->Filter = "Imagenes|*.jpg;*.png;*.bmp";

    if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        std::string filename = msclr::interop::marshal_as<std::string>(dialog->FileName);

        *frame = cv::imread(filename);

        if (!frame->empty())
            pictureBox->Image = MatToBitmap(*frame);
    }
}

void MyForm1::BtnStartCamera_Click(Object^ sender, EventArgs^ e)
{
    ClearDisplay();
    if (!cap->isOpened())
    {
        cap->open(0);
        if (cap->isOpened())
            timer->Start();
    }
}

void MyForm1::BtnStopCamera_Click(Object^ sender, EventArgs^ e)
{
    ClearDisplay();
    timer->Stop();
    if (cap->isOpened())
        cap->release();
}

void MyForm1::Timer_Tick(Object^ sender, EventArgs^ e)
{
    if (cap->isOpened())
    {
        (*cap) >> (*frame);

        if (!frame->empty())
            pictureBox->Image = MatToBitmap(*frame);
    }
}

Bitmap^ MyForm1::MatToBitmap(cv::Mat& mat)
{
    cv::Mat img;

    if (mat.channels() == 1)
        cv::cvtColor(mat, img, cv::COLOR_GRAY2BGR);
    else
        img = mat;

    if (img.empty())
        return nullptr;

    Bitmap^ bmp = gcnew Bitmap(img.cols, img.rows, PixelFormat::Format24bppRgb);

    BitmapData^ bmpData = bmp->LockBits(
        System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height),
        ImageLockMode::WriteOnly,
        PixelFormat::Format24bppRgb
    );

    unsigned char* dst = (unsigned char*)bmpData->Scan0.ToPointer();
    unsigned char* src = img.data;

    int srcStride = img.step;
    int dstStride = bmpData->Stride;

    for (int y = 0; y < img.rows; y++)
    {
        memcpy(
            dst + y * dstStride,
            src + y * srcStride,
            img.cols * 3
        );
    }

    bmp->UnlockBits(bmpData);

    return bmp;
}

