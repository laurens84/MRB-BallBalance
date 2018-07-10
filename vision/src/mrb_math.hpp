#ifndef MRB_MATH_HPP
#define MRB_MATH_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>

namespace MRB_MATH {
inline bool triangle_check(const cv::Point &a, const cv::Point &b, const cv::Point &c, uint8_t leeway) {
    leeway -= (leeway % 2); // Substract 1 if odd number.

    double side_1 = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    double side_2 = sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2));
    double side_3 = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));
    double side_avg = (side_1 + side_2 + side_3) / 3;

    return ((side_1 - side_avg > -leeway / 2) && (side_1 - side_avg < leeway / 2)) ? true : false;
}

inline double dot(const cv::Point &a, const cv::Point &b) {
    return (a.x * b.x) + (a.y * b.y);
}

inline double absolute(const cv::Point &a) {
    return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

inline double scalar_proj(const cv::Point &a, const cv::Point &b) {
    return dot(a, b) / absolute(a);
}

} // namespace MRB_MATH

#endif // MRB_MATH_HPP
