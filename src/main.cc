#include <cstdlib>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>

#include "subsystem/perception/detection/lane_detector_strategy.h"
#include "subsystem/perception/detection/basic_lane_detector.h"

namespace {
  const char kTestVideo[] = "../test_video/source/solidYellowLeft.mp4";
}

int main() {
  cv::VideoCapture stream(kTestVideo); // open test video file
  if(!stream.isOpened()) { // check if we succeeded
    return EXIT_FAILURE;
  }

  cv::namedWindow("Lane Lines detection", cv::WINDOW_AUTOSIZE);

  for(;;)
  {
    cv::Mat frame;
    stream >> frame; // get a new frame from camera

    if (frame.empty()) break;

    LaneDetectorStrategy<BasicLaneDetector> detector;
    cv::Mat edges = detector.useStrategy(frame);
    cv::imshow("edges", edges);

    if(cv::waitKey(15) >= 0) break;
  }

  return EXIT_SUCCESS;
}