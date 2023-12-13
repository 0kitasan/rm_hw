#include <assert.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

void show_img(const std::string &name, cv::Mat img) {
  // 由于默认情况下，cv::imshow()的窗口较大，因此主动调整窗口大小
  cv::namedWindow(name, cv::WINDOW_NORMAL);
  cv::resizeWindow(name, 800, 600);
  cv::imshow(name, img);
}

void proc_img(const std::string &n, cv::Mat &img, int &k1, int &k2) {

  // 开运算去除噪点
  cv::Mat kernel1 = getStructuringElement(cv::MORPH_CROSS, cv::Size(k1, k1));
  morphologyEx(img, img, cv::MORPH_OPEN, kernel1);
  show_img(n + "open", img);

  //  闭运算连接内部
  cv::Mat kernel2 = getStructuringElement(cv::MORPH_CROSS, cv::Size(k2, k2));
  morphologyEx(img, img, cv::MORPH_CLOSE, kernel2);
  show_img(n + "close", img);
}

int main() {
  int open_size = 8, close_size = 12;
  cv::Mat src = cv::imread("../001.jpg");
  assert(!src.empty());
  show_img("src", src);
  cv::Mat hsv;
  cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
  cv::Mat hsv_proc1, hsv_proc2, hsv_proc3;
  cv::inRange(hsv, cv::Scalar(110, 43, 46), cv::Scalar(124, 255, 255),
              hsv_proc1);

  show_img("hsv_proc1", hsv_proc1);
  /*
  // 开运算去除噪点
    cv::Mat kernel1 = getStructuringElement(cv::MORPH_CROSS, cv::Size(8, 8));
    morphologyEx(hsv_proc1, hsv_proc2, cv::MORPH_OPEN, kernel1);
    show_img("hsv_proc2", hsv_proc2);

    //  闭运算连接内部
    cv::Mat kernel2 = getStructuringElement(cv::MORPH_CROSS, cv::Size(12, 12));
    morphologyEx(hsv_proc2, hsv_proc3, cv::MORPH_CLOSE, kernel2);
    show_img("hsv_proc3", hsv_proc3);
  */
  proc_img("hsv_res1", hsv_proc1, open_size, close_size);

  cv::waitKey(0);
  return 0;
}
