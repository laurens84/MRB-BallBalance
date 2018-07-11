/**
 * @brief The mrb_math file contains a namespace used to store mathematical functions required by the module.
 *
 * @file circle_detector.hpp
 * @date 2018-07-11
 */

#ifndef MRB_MATH_HPP
#define MRB_MATH_HPP

#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>

namespace MRB_MATH {

/**
 * @brief Returns the absolute value of a number if applicable.
 *
 * @param v     The value to be converted.
 * @return T    Returns the absolute value of v.
 */
template <typename T>
inline T abs(const T &v) {
    return (v < 0) ? v * -1 : v;
}

/**
 * @brief Returns the dot product of two vectors.
 *
 * @param a         The first vector.
 * @param b         The second vector.
 * @return double   The dot product of vector a and b.
 */
inline double dot(const cv::Point &a, const cv::Point &b) {
    return (a.x * b.x) + (a.y * b.y);
}

/**
 * @brief Returns the absolute value of a vector.
 *
 * @param a         The vector.
 * @return double   Returns the absolute value of vector a.
 */
inline double absolute(const cv::Point &a) {
    return sqrt(pow(abs<int>(a.x), 2) + pow(abs<int>(a.y), 2));
}

/**
 * @brief Returns the absolute value of vector a - b.
 *
 * @param a         The vector that will be substracted from.
 * @param b         The substraction vector.
 * @return double   Returns the absolute value of vector a - b.
 */
inline double absolute_sub(const cv::Point &a, const cv::Point &b) {
    return sqrt(pow(abs<int>(a.x - b.x), 2) + pow(abs<int>(a.y - b.y), 2));
}

/**
 * @brief Checks whether three given points form the shape of a triangle.
 *
 * @param a         The first point.
 * @param b         The second point.
 * @param c         The third point.
 * @param leeway    The amount of leeway expressed in pixels.
 * @return true     If the three points make a triangle.
 * @return false    If the three points don't make a triangle.
 */
inline bool triangle_check(const cv::Point &a, const cv::Point &b, const cv::Point &c, uint16_t leeway) {
    leeway -= (leeway % 2); // Substract 1 if odd number.

    double side_1 = absolute_sub(a, b);
    double side_2 = absolute_sub(a, c);
    double side_3 = absolute_sub(b, c);
    double side_avg = (side_1 + side_2 + side_3) / 3;

    return ((side_1 - side_avg > -leeway / 2) && (side_1 - side_avg < leeway / 2)) ? true : false;
}

/**
 * @brief Returns the scalar projection of two vectors.
 *
 * @param a         The first vector.
 * @param b         The second vector, projected on a.
 * @return double   Returns the scalar projection of vector b on a.
 */
inline double scalar_proj(const cv::Point &a, const cv::Point &b) {
    return dot(a, b) / absolute(a);
}

} // namespace MRB_MATH

#endif // MRB_MATH_HPP
