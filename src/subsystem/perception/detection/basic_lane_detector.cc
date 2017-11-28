#include <opencv/cv.hpp>

#include "basic_lane_detector.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
cv::Mat BasicLaneDetector::execute(const cv::Mat& frame) {
  cv::Mat edges;
  cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
  cv::Canny(edges, edges, 50, 150, 3);
  cv::dilate(edges, edges, cv::Mat());

  std::vector<cv::Vec4i> lines;
  cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 35, 10, 10);

  for (const auto& l : lines) {
    cv::line(frame, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
  }

  return frame;
}

#pragma clang diagnostic pop