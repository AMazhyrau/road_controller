#include <opencv/cv.hpp>

#include "basic_lane_detector.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
cv::Mat BasicLaneDetector::execute(const cv::Mat& frame) {
  cv::Mat normImage = normalizeImage(frame);
  normImage = cropImage(normImage);
  cv::Mat bwImage = selectColors(normImage);

  std::vector<cv::Vec4i> lines = detectLaneLines(bwImage);

  for (const auto& l : lines) {
    cv::line(frame, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
  }

  return frame;
}

cv::Mat BasicLaneDetector::normalizeImage(const cv::Mat &frame) {
  cv::Mat labImage;
  cv::cvtColor(frame, labImage, cv::COLOR_BGR2Lab);

  // Extract L-channel
  std::vector<cv::Mat> labChannels(3);
  cv::split(labImage, labChannels);

  // Apply CLAHE algorithm to L-channel
  cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
  clahe->setClipLimit(3.0);
  cv::Mat normLight;
  clahe->apply(labChannels[0], normLight);

  // Merge color channels back to Lab image
  normLight.copyTo(labChannels[0]);
  cv::merge(labChannels, labImage);

  // Convert to RGB
  cv::Mat normImage;
  cv::cvtColor(labImage, normImage, cv::COLOR_Lab2RGB);

  cv::GaussianBlur(normImage, normImage, cv::Size(7,7), 1.5, 1.5);
  return normImage;
}

cv::Mat BasicLaneDetector::cropImage(const cv::Mat& image) {
  // FIXME: implement crop method;
  return image;
}

std::vector<cv::Vec4i> BasicLaneDetector::detectLaneLines(const cv::Mat& image) {
  cv::Mat edges;
  cv::Canny(image, edges, 50, 150, 3);
  cv::dilate(edges, edges, cv::Mat());

  std::vector<cv::Vec4i> lines;
  cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 35, 10, 10);

  return lines;
}

cv::Mat BasicLaneDetector::selectColors(const cv::Mat& image) {
  cv::Mat whiteMask;
  cv::inRange(image, cv::Scalar(200, 200, 200), cv::Scalar(255, 255, 255), whiteMask);

  cv::Mat yellowMask;
  cv::inRange(image, cv::Scalar(190, 190, 0), cv::Scalar(255, 255, 255), yellowMask);

  cv::Mat mask;
  cv::bitwise_or(whiteMask, yellowMask, mask);

  cv::Mat bwImage;
  cv::bitwise_and(image, image, bwImage, mask);

  cv::cvtColor(bwImage, bwImage, cv::COLOR_RGB2GRAY);

  return bwImage;
}

#pragma clang diagnostic pop