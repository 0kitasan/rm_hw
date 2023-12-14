#include <assert.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
int main() {
  cv::Mat img = cv::imread("/home/xyt/rm_hw/hw1/apple.png");
  assert(!img.empty());
  // cv::imshow("source", img);
  cv::Mat hsv;
  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
  // cv::imshow("hsvimg", hsv);

  cv::Mat hsv_red_1, hsv_red_2, hsv_orange; // 红色的h有两个范围
  inRange(hsv, cv::Scalar(0, 100, 46), cv::Scalar(12, 255, 255), hsv_red_1);
  inRange(hsv, cv::Scalar(153, 43, 46), cv::Scalar(180, 255, 255), hsv_red_2);
  inRange(hsv, cv::Scalar(14, 180, 80), cv::Scalar(25, 255, 255), hsv_orange);
  // cv::imshow("red1", hsv_red_1);
  // cv::imshow("red2", hsv_red_2);
  // cv::imshow("orange", hsv_orange);

  cv::Mat hsv_result = hsv_red_1 | hsv_red_2 | hsv_orange;
  // cv::imshow("result0", hsv_result);
  //  闭运算连接内部
  cv::Mat kernel2 = getStructuringElement(cv::MORPH_CROSS, cv::Size(6, 6));
  morphologyEx(hsv_result, hsv_result, cv::MORPH_CLOSE, kernel2);
  // cv::imshow("result1", hsv_result);

  // 开运算去除噪点
  cv::Mat kernel1 = getStructuringElement(cv::MORPH_CROSS, cv::Size(14, 14));
  morphologyEx(hsv_result, hsv_result, cv::MORPH_OPEN, kernel1);
  // cv::imshow("result2", hsv_result);

  morphologyEx(hsv_result, hsv_result, cv::MORPH_CLOSE, kernel2);
  // cv::imshow("result3", hsv_result);

  std::vector<cv::Vec4i> hierarchy;
  std::vector<std::vector<cv::Point>> all_contours;
  cv::findContours(hsv_result, all_contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_NONE);
  cv::Rect boundRect;
  int i, n;
  i = n = 0;
  for (auto contours : all_contours) {
    std::cout << cv::contourArea(contours) << std::endl;
    if (cv::contourArea(contours) > 1000) {
      n = i;
      boundRect = cv::boundingRect(cv::Mat(contours));
      break;
    }
    i++;
  }

  cv::drawContours(img, all_contours, n, cv::Scalar(0, 255, 0), 2);
  cv::rectangle(img, boundRect, cv::Scalar(0, 255, 0), 2);
  cv::imshow("output", img);
  cv::imwrite("output.png", img);
  cv::waitKey(0);
  return 0;
}
