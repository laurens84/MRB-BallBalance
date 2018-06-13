#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class display {
  private:
    std::string window_name;
    cv::Point mouse_pos;

    static void mouseHandler(int evt, int x, int y, int flags, void *param);

  public:
    display(const std::string &window_name);

    void display_circles(cv::Mat &frame, std::vector<cv::Point> &points) const;

    cv::Point &getMousePos();
};
#endif // DISPLAY_HPP