#include "main.hpp"

void main()
{
  std::string inputFile = "D:/tmp/tmp/01414-1568727517/01414-1568727517-sensor-1.mkv";
  cv::VideoCapture cap(inputFile);
  if (!cap.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    return;
  }
  for (int i = 0; i < 10; i++) {
    cv::Mat frame;
    cap >> frame;
  }
  return;
}
