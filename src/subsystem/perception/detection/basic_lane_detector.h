#ifndef ROAD_CONTROLLER_LANE_DETECTOR_H
#define ROAD_CONTROLLER_LANE_DETECTOR_H

#include "lane_detector_strategy.h"

class BasicLaneDetector {
 protected:
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
  cv::Mat execute(const cv::Mat&);
#pragma clang diagnostic pop
};

#endif //ROAD_CONTROLLER_LANE_DETECTOR_H
