#ifndef ROAD_CONTROLLER_LANE_DETECTOR_INTERFACE_H
#define ROAD_CONTROLLER_LANE_DETECTOR_INTERFACE_H

#include <opencv2/core/mat.hpp>

template <class Strategy>
class LaneDetectorStrategy : public Strategy {
 public:
  cv::Mat useStrategy(const cv::Mat& videoFrame) {
    return this->execute(videoFrame);
  }
};
#endif //ROAD_CONTROLLER_LANE_DETECTOR_INTERFACE_H
