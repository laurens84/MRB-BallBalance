#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

int main()
{
  cv::VideoCapture cap(0);
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 400);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 500);
  if (!cap.isOpened())
    return -1;

  int b = 0;
  cv::namedWindow("Circles", cv::WINDOW_AUTOSIZE);

  while (1)
  {
    cv::Mat frame, gray;

    cap >> frame;

    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(gray, gray, cv::Size(17, 17), 0);

    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 4, 100, 20, 8, 10);

    for (size_t i = 0; i < circles.size(); i++)
    {
      std::cout << b++ << " circle found.\n";
      cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      cv::circle(frame, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
      cv::circle(frame, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }

    cv::imshow("circles", frame);
    if (cv::waitKey(30) == 'c')
      break;
  }

  return 0;
}