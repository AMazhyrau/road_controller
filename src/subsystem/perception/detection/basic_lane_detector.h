#ifndef ROAD_CONTROLLER_LANE_DETECTOR_H
#define ROAD_CONTROLLER_LANE_DETECTOR_H

#include "lane_detector_strategy.h"

class BasicLaneDetector {
 protected:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
  cv::Mat execute(const cv::Mat&);
#pragma clang diagnostic pop
 private:
  cv::Mat normalizeImage(const cv::Mat&);
  cv::Mat cropImage(const cv::Mat&);
  cv::Mat selectColors(const cv::Mat&);
  std::vector<cv::Vec4i> detectLaneLines(const cv::Mat&);
};

#endif //ROAD_CONTROLLER_LANE_DETECTOR_H
