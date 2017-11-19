#include <opencv/cv.hpp>

#include "basic_lane_detector.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
cv::Mat BasicLaneDetector::execute(const cv::Mat& frame) {
  cv::Mat edges;
  cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
  cv::Canny(edges, edges, 50, 150);
  cv::dilate(edges, edges, cv::Mat());

  return edges;
}
#pragma clang diagnostic pop
