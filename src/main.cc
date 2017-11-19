#include <cstdlib>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>

#include "subsystem/perception/detection/lane_detector_strategy.h"
#include "subsystem/perception/detection/basic_lane_detector.h"

int main() {
  cv::VideoCapture cap(0); // open the default camera
  if(!cap.isOpened()) { // check if we succeeded
    return -1;
  }

  cv::namedWindow("edges",1);
  for(;;)
  {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    LaneDetectorStrategy<BasicLaneDetector> detector;
    cv::Mat edges = detector.useStrategy(frame);
    cv::imshow("edges", edges);

    if(cv::waitKey(30) >= 0) break;
  }

  return EXIT_SUCCESS;
}
