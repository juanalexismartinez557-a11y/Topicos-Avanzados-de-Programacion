#include "MyForm1.h"
#include <msclr/marshal_cppstd.h>

int thresholdValue = 128;
int cannyValue = 100;
int sobelValue = 1;
int zoomPercent = 100;

cv::Mat originalImage;

cv::Mat MyForm1::ApplyFilters(cv::Mat input)
{
    cv::Mat result, temp;

    if (input.empty())
        return input;

    switch (currentFilter)
    {
    case FilterType::Grayscale:
        cv::cvtColor(input, result, cv::COLOR_BGR2GRAY);
        break;

    case FilterType::ThresholdBW:
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
        cv::threshold(temp, result, thresholdValue, 255, cv::THRESH_BINARY);
        break;

    case FilterType::ThresholdWB:
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
        cv::threshold(temp, result, thresholdValue, 255, cv::THRESH_BINARY_INV);
        break;

    case FilterType::Canny:
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
        cv::Canny(temp, result, cannyValue, cannyValue * 2);
        break;

    case FilterType::Sobel:
        cv::cvtColor(input, temp, cv::COLOR_BGR2GRAY);
        cv::Sobel(temp, result, CV_8U, sobelValue, sobelValue);
        break;

    case FilterType::RGBSplit:
    {
        std::vector<cv::Mat> channels;
        cv::split(input, channels);

        cv::Mat zero = cv::Mat::zeros(input.size(), CV_8UC1);

        std::vector<cv::Mat> merged;
        merged.push_back(zero);
        merged.push_back(zero);
        merged.push_back(channels[2]);

        cv::merge(merged, result);
        break;
    }

    default:
        result = input.clone();
        break;
    }

    double scale = zoomPercent / 100.0;
    if (scale != 1.0) {
        cv::Mat zoomed;

        if (scale > 1.0) {
            // ZOOM IN
            int centerX = result.cols / 2;
            int centerY = result.rows / 2;

            int newWidth = static_cast<int>(result.cols / scale);
            int newHeight = static_cast<int>(result.rows / scale);

            // Validar límites
            if (newWidth > result.cols) newWidth = result.cols;
            if (newHeight > result.rows) newHeight = result.rows;

            int x1 = centerX - newWidth / 2;
            int y1 = centerY - newHeight / 2;

            if (x1 < 0) x1 = 0;
            if (y1 < 0) y1 = 0;

            if (x1 + newWidth > result.cols) x1 = result.cols - newWidth;
            if (y1 + newHeight > result.rows) y1 = result.rows - newHeight;

            cv::Rect roi(x1, y1, newWidth, newHeight);
            cv::Mat cropped = result(roi).clone();

            cv::resize(cropped, zoomed, result.size(), 0, 0, cv::INTER_CUBIC);
            result = zoomed;
        }
        else {
            // ZOOM OUT
            cv::resize(result, zoomed, cv::Size(), scale, scale, cv::INTER_AREA);
            cv::Mat canvas = cv::Mat::zeros(result.size(), result.type());
            int offsetX = (result.cols - zoomed.cols) / 2;
            int offsetY = (result.rows - zoomed.rows) / 2;
            zoomed.copyTo(canvas(cv::Rect(offsetX, offsetY, zoomed.cols, zoomed.rows)));
            result = canvas;
        }
    }

    if (!result.isContinuous())
    {
        result = result.clone();
    }


    return result;
}


MyForm1::MyForm1(void)
{
    InitializeComponent();
    cap = new cv::VideoCapture();
    frame = new cv::Mat();

	currentFilter = FilterType::None;
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
    this->Width = 1000;
    this->Height = 700;
    this->Text = "OpenCV - Imagen y Camara";

    // -------- PictureBox (centro) --------
    pictureBox = gcnew PictureBox();
    pictureBox->Dock = DockStyle::Fill;
    pictureBox->SizeMode = PictureBoxSizeMode::Zoom;

    // -------- Panel superior --------
    Panel^ topPanel = gcnew Panel();
    topPanel->Dock = DockStyle::Top;
    topPanel->Height = 60;

    // -------- Panel inferior --------
    Panel^ bottomPanel = gcnew Panel();
    bottomPanel->Dock = DockStyle::Bottom;
    bottomPanel->Height = 220;

    // ===== BOTONES SUPERIORES =====
    btnLoadImage = gcnew Button();
    btnLoadImage->Text = "Cargar Imagen";
    btnLoadImage->Width = 150;
    btnLoadImage->Left = 20;
    btnLoadImage->Top = 15;
    btnLoadImage->Click += gcnew EventHandler(this, &MyForm1::BtnLoadImage_Click);

    btnStartCamera = gcnew Button();
    btnStartCamera->Text = "Iniciar Camara";
    btnStartCamera->Width = 150;
    btnStartCamera->Left = 200;
    btnStartCamera->Top = 15;
    btnStartCamera->Click += gcnew EventHandler(this, &MyForm1::BtnStartCamera_Click);

    btnStopCamera = gcnew Button();
    btnStopCamera->Text = "Detener Camara";
    btnStopCamera->Width = 150;
    btnStopCamera->Left = 380;
    btnStopCamera->Top = 15;
    btnStopCamera->Click += gcnew EventHandler(this, &MyForm1::BtnStopCamera_Click);

    // ===== BOTONES INFERIORES =====
    btnGray = gcnew Button();
    btnGray->Text = "Grises";
    btnGray->Top = 10;
    btnGray->Left = 20;
    btnGray->Click += gcnew EventHandler(this, &MyForm1::BtnGray_Click);

    btnBinary = gcnew Button();
    btnBinary->Text = "Binario B/N";
    btnBinary->Top = 10;
    btnBinary->Left = 120;
    btnBinary->Click += gcnew EventHandler(this, &MyForm1::BtnBinary_Click);

    btnBinaryInv = gcnew Button();
    btnBinaryInv->Text = "Binario N/B";
    btnBinaryInv->Top = 10;
    btnBinaryInv->Left = 240;
    btnBinaryInv->Click += gcnew EventHandler(this, &MyForm1::BtnBinaryInv_Click);

    btnCanny = gcnew Button();
    btnCanny->Text = "Canny";
    btnCanny->Top = 10;
    btnCanny->Left = 360;
    btnCanny->Click += gcnew EventHandler(this, &MyForm1::BtnCanny_Click);

    btnSobel = gcnew Button();
    btnSobel->Text = "Sobel";
    btnSobel->Top = 10;
    btnSobel->Left = 460;
    btnSobel->Click += gcnew EventHandler(this, &MyForm1::BtnSobel_Click);

    btnRGB = gcnew Button();
    btnRGB->Text = "RGB";
    btnRGB->Top = 10;
    btnRGB->Left = 560;
    btnRGB->Click += gcnew EventHandler(this, &MyForm1::BtnRGB_Click);

    btnReset = gcnew Button();
    btnReset->Text = "Original";
    btnReset->Top = 10;
    btnReset->Left = 660;
    btnReset->Click += gcnew EventHandler(this, &MyForm1::BtnReset_Click);

    // ===== TrackBars con Labels =====

// Label y TrackBar para Threshold
    lblThreshold = gcnew Label();
    lblThreshold->Text = "Umbral: 128";
    lblThreshold->Left = 20;
    lblThreshold->Top = 40;
    lblThreshold->AutoSize = true;

    trackBarThreshold = gcnew TrackBar();
    trackBarThreshold->Minimum = 0;
    trackBarThreshold->Maximum = 255;
    trackBarThreshold->Value = 128;
    trackBarThreshold->Width = 300;
    trackBarThreshold->Left = 20;
    trackBarThreshold->Top = 60;
    trackBarThreshold->Scroll += gcnew EventHandler(this, &MyForm1::TrackBarThreshold_Scroll);

    // Label y TrackBar para Canny
    lblCanny = gcnew Label();
    lblCanny->Text = "Canny: 100";
    lblCanny->Left = 350;
    lblCanny->Top = 40;
    lblCanny->AutoSize = true;

    trackBarCanny = gcnew TrackBar();
    trackBarCanny->Minimum = 0;
    trackBarCanny->Maximum = 255;
    trackBarCanny->Value = 100;
    trackBarCanny->Width = 300;
    trackBarCanny->Left = 350;
    trackBarCanny->Top = 60;
    trackBarCanny->Scroll += gcnew EventHandler(this, &MyForm1::TrackBarCanny_Scroll);

    // Label y TrackBar para Zoom
    lblZoom = gcnew Label();
    lblZoom->Text = "Zoom: 100%";
    lblZoom->Left = 20;
    lblZoom->Top = 110;
    lblZoom->AutoSize = true;

    trackBarZoom = gcnew TrackBar();
    trackBarZoom->Minimum = 10;
    trackBarZoom->Maximum = 200;
    trackBarZoom->Value = 100;
    trackBarZoom->Width = 300;
    trackBarZoom->Left = 20;
    trackBarZoom->Top = 130;
    trackBarZoom->Scroll += gcnew EventHandler(this, &MyForm1::TrackBarZoom_Scroll);

    // ===== Timer =====
    timer = gcnew Timer();
    timer->Interval = 30;
    timer->Tick += gcnew EventHandler(this, &MyForm1::Timer_Tick);

    // ===== Agregar controles =====
    this->Controls->Add(pictureBox);
    this->Controls->Add(topPanel);
    this->Controls->Add(bottomPanel);

    topPanel->Controls->Add(btnLoadImage);
    topPanel->Controls->Add(btnStartCamera);
    topPanel->Controls->Add(btnStopCamera);

    bottomPanel->Controls->Add(btnGray);
    bottomPanel->Controls->Add(btnBinary);
    bottomPanel->Controls->Add(btnBinaryInv);
    bottomPanel->Controls->Add(btnCanny);
    bottomPanel->Controls->Add(btnSobel);
    bottomPanel->Controls->Add(btnRGB);
    bottomPanel->Controls->Add(lblThreshold);        
    bottomPanel->Controls->Add(trackBarThreshold);
    bottomPanel->Controls->Add(lblCanny);            
    bottomPanel->Controls->Add(trackBarCanny);
    bottomPanel->Controls->Add(lblZoom);            
    bottomPanel->Controls->Add(trackBarZoom);
    bottomPanel->Controls->Add(btnReset);
}


void MyForm1::ClearDisplay()
{
    timer->Stop();

    if (cap->isOpened())
        cap->release();

    // Limpiar imagen del PictureBox
    if (pictureBox->Image != nullptr)
    {
        delete pictureBox->Image;
        pictureBox->Image = nullptr;
    }

    // Limpiar imagen almacenada
    originalImage.release();

    // Resetear filtro
    currentFilter = FilterType::None;
}


void MyForm1::BtnLoadImage_Click(Object^ sender, EventArgs^ e)
{
    ClearDisplay();

    OpenFileDialog^ dialog = gcnew OpenFileDialog();
    dialog->Filter = "Imagenes|*.jpg;*.png;*.bmp";

    if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        std::string filename = msclr::interop::marshal_as<std::string>(dialog->FileName);

        *frame = cv::imread(filename);

        if (!frame->empty())
        {
            originalImage = frame->clone();
            cv::Mat processed = ApplyFilters(originalImage);
            pictureBox->Image = MatToBitmap(processed);
        }
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
}

void MyForm1::Timer_Tick(Object^ sender, EventArgs^ e)
{
    if (cap->isOpened())
    {
        (*cap) >> (*frame);

        if (!frame->empty())
        {
            cv::Mat processed = ApplyFilters(*frame);
            pictureBox->Image = MatToBitmap(processed);
        }
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

    int copyWidth = min(srcStride, dstStride);

    for (int y = 0; y < img.rows; y++)
    {
        memcpy(
            dst + y * dstStride,
            src + y * srcStride,
            copyWidth
        );
    }


    bmp->UnlockBits(bmpData);

    return bmp;
}

void MyForm1::BtnGray_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::Grayscale;

    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }
}

void MyForm1::BtnBinary_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::ThresholdBW;

    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }
}

void MyForm1::BtnBinaryInv_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::ThresholdWB;

    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }
}

void MyForm1::BtnCanny_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::Canny;
    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }
}

void MyForm1::BtnSobel_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::Sobel;
    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }
}

void MyForm1::BtnRGB_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::RGBSplit;
    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }

}

void MyForm1::BtnReset_Click(Object^ sender, EventArgs^ e)
{
    currentFilter = FilterType::None;

    if (!originalImage.empty())
    {
        pictureBox->Image = MatToBitmap(originalImage);
    }
}


void MyForm1::TrackBarThreshold_Scroll(Object^ sender, EventArgs^ e)
{
    thresholdValue = trackBarThreshold->Value;
    lblThreshold->Text = "Umbral (solo funciona con Boton Binario activado): " + thresholdValue.ToString();
    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }

}

void MyForm1::TrackBarCanny_Scroll(Object^ sender, EventArgs^ e)
{
    cannyValue = trackBarCanny->Value;
    lblCanny->Text = "Canny: (solo funciona con boton Canny activado)" + cannyValue.ToString();
    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }

}

void MyForm1::TrackBarZoom_Scroll(Object^ sender, EventArgs^ e)
{
    zoomPercent = trackBarZoom->Value;
    lblZoom->Text = "Zoom: " + zoomPercent.ToString() + "%";
    if (!originalImage.empty())
    {
        cv::Mat processed = ApplyFilters(originalImage);
        pictureBox->Image = MatToBitmap(processed);
    }

}
