#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

std::string chars = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
// Строка символов, используемых для представления яркости пикселей
// Чем символ ближе к началу строки, тем меньше яркость, и наоборот
int char_width = 6;  // Ширина символа в пикселях
int char_height = 8;  // Высота символа в пикселях
int char_len = chars.length();  // Количество символов в строке
float interval = char_len / 256.0f;  // Интервал между символами для преобразования яркости пикселей в символы

char getChar(float value)
{
    // Функция для получения символа, соответствующего заданной яркости пикселя
    int index = static_cast<int>(value * interval);
    return chars[index];
}

void video_to_ASCII(const std::string& filename)
{
    // Функция для преобразования видео в ASCII-анимацию
    cv::VideoCapture cap(filename);
    if (!cap.isOpened())
    {
        std::cout << "Could not open the video file." << std::endl;
        return;
    }

    cv::Mat frame;
    cv::Mat resizedFrame;

    cv::namedWindow("Video_to_ASCII", cv::WINDOW_NORMAL);

    cv::Scalar text_color(98, 160, 3);  // Цвет текста

    while (true)
    {
        cap >> frame;

        if (frame.empty())
            break;

        // Изменение размера кадра для преобразования в ASCII
        cv::resize(frame, resizedFrame, cv::Size(frame.cols / char_width, frame.rows / char_height), 0, 0, cv::INTER_NEAREST);

        cv::Mat outputImage(frame.rows, frame.cols, CV_8UC3, cv::Scalar(0, 0, 0));

        for (int i = 0; i < resizedFrame.rows; i++)
        {
            for (int j = 0; j < resizedFrame.cols; j++)
            {
                // Получение относительной яркости пикселя и соответствующего символа
                cv::Vec3b color = resizedFrame.at<cv::Vec3b>(i, j);
                //Источник формулы: https://habr.com/ru/articles/304210/
                int h = static_cast<int>(0.2126 * color[2] + 0.7152 * color[1] + 0.0722 * color[0]);
                char c = getChar(h);

                // Ввод символа на изображение
                cv::putText(outputImage, std::string(1, c), cv::Point(j * char_width, i * char_height), cv::FONT_HERSHEY_PLAIN, 1.0, text_color, 1, cv::LINE_AA, false);
            }
        }

        cv::imshow("Video_to_ASCII", outputImage);

        int key = cv::waitKey(1);
        if (key == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();
}

void cam_to_ASCII()
{

    // Функция для преобразования веб-камеры в ASCII-анимацию
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 750);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 450);

    cv::Mat img;
    cv::Mat resizedImg;

    cv::namedWindow("Cam_to_ASCII", cv::WINDOW_NORMAL);

    cv::Scalar text_color(98, 160, 3);  // Цвет текста

    while (true)
    {
        cap >> img;

        cv::resize(img, resizedImg, cv::Size(img.cols / char_width, img.rows / char_height), 0, 0, cv::INTER_NEAREST);

        cv::Mat outputImage(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));

        for (int i = 0; i < resizedImg.rows; i++)
        {
            for (int j = 0; j < resizedImg.cols; j++)
            {
                cv::Vec3b color = resizedImg.at<cv::Vec3b>(i, j);
                int h = static_cast<int>(0.2126 * color[2] + 0.7152 * color[1] + 0.0722 * color[0]);
                char c = getChar(h);

                cv::putText(outputImage, std::string(1, c), cv::Point(j * char_width, i * char_height), cv::FONT_HERSHEY_PLAIN, 1.0, text_color, 1, cv::LINE_AA, false);
            }
        }

        cv::imshow("Cam_to_ASCII", outputImage);

        int key = cv::waitKey(1);
        if (key == 'q')
            break;
    }

    cap.release();
    cv::destroyAllWindows();
}

void jpeg_to_ASCII(const std::string& filename)
{
    // Функция для преобразования изображения в ASCII
    cv::Mat img = cv::imread(filename);

    if (img.empty())
    {
        std::cout << "Could not open or find the image: " << filename << std::endl;
        return;
    }

    cv::Mat resizedImg;
    cv::resize(img, resizedImg, cv::Size(img.cols / char_width, img.rows / char_height), 0, 0, cv::INTER_NEAREST);

    cv::Mat outputImage(img.rows, img.cols, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::Scalar text_color(9, 115, 150);  // Цвет текста

    for (int i = 0; i < resizedImg.rows; i++)
    {
        for (int j = 0; j < resizedImg.cols; j++)
        {
            cv::Vec3b color = resizedImg.at<cv::Vec3b>(i, j);
            int h = static_cast<int>(0.2126 * color[2] + 0.7152 * color[1] + 0.0722 * color[0]);
            char c = getChar(h);

            cv::putText(outputImage, std::string(1, c), cv::Point(j * char_width, i * char_height), cv::FONT_HERSHEY_PLAIN, 1.0, text_color, 1, cv::LINE_AA, false);
        }
    }

    cv::imshow("JPEG_to_ASCII", outputImage);
    cv::waitKey(0);
}

std::string ASCII_generator(std::string answer1) {
    if (std::stoi(answer1) == 1) {
        std::string filename;
        std::cout << "Insert path to file" << std::endl;
        std::cin >> filename;
        jpeg_to_ASCII(filename);
        return "img";
    }
    else if (std::stoi(answer1) == 2) {
        std::cout << "Press q to exit" << std::endl;
        std::string filename;
        std::cout << "Insert path to file" << std::endl;
        std::cin >> filename;
        video_to_ASCII(filename);
        return "vid";
    }
    else if (std::stoi(answer1) == 3) {
        std::cout << "Press q to exit" << std::endl;
        cam_to_ASCII();
        return "cam";
    }

    else {
        return "Please choose again correctly";
    }
}

int main() {
    std::cout << "CHOOSE (1-3)\n"
              << "1) JPEG to ASCII\n"
              << "2) Video to ASCII\n"
              << "3) Camera to ASCII" << std::endl;

    std::string answer1;
    std::cin >> answer1;
    std::cout << ASCII_generator(answer1) << std::endl;

    return 0;
}