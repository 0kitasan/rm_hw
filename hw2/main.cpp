#include <assert.h>
#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <vector>

void show_img(const std::string &name, const cv::Mat img) {
  // 由于默认情况下，cv::imshow()的窗口较大，因此主动调整窗口大小
  cv::namedWindow(name, cv::WINDOW_NORMAL);
  cv::resizeWindow(name, 600, 400);
  cv::imshow(name, img);
}

void proc_img(const std::string &n, const cv::Mat &img_src, cv::Mat &img_dst,
              int &k1, int &k2) {
  // hsv颜色提取
  cv::cvtColor(img_src, img_dst, cv::COLOR_BGR2HSV);
  cv::inRange(img_dst, cv::Scalar(106, 55, 120), cv::Scalar(124, 255, 255),
              img_dst);
  // show_img(n + "-hsv", img_dst);

  // 开运算去除噪点
  cv::Mat kernel1 = getStructuringElement(cv::MORPH_CROSS, cv::Size(k1, k1));
  morphologyEx(img_dst, img_dst, cv::MORPH_OPEN, kernel1);
  // show_img(n + "-open", img);

  //  闭运算连接内部
  cv::Mat kernel2 = getStructuringElement(cv::MORPH_RECT, cv::Size(k2, k2));
  morphologyEx(img_dst, img_dst, cv::MORPH_CLOSE, kernel2);
  // show_img(n + "-close", img);
}

void plate_contour() {}

void plate_judge() {}

int main() {
  // 开运算与闭运算参数
  int open_size = 4, close_size = 18;

  std::vector<std::string> img_path = {"../001.jpg", "../002.jpg", "../003.jpg",
                                       "../004.jpg", "../005.jpg"};
  std::vector<std::string> img_name = {"img1", "img2", "img3", "img4", "img5"};
  std::vector<cv::Mat> src_imgs;
  std::vector<cv::Mat> res_imgs;
  for (int i = 0; i < 5; i++) {
    // 读取图像并存储在src_imgs
    cv::Mat img = cv::imread(img_path[i]);
    assert(!img.empty());
    src_imgs.push_back(img);
    // show_img(img_name[i] + "-origin", src_imgs[i]);
  }

  for (int i = 0; i < 5; i++) {
    // 处理图像并存储在res_imgs
    assert(!src_imgs[i].empty());
    // show_img(img_name[i] + "-origin", src_imgs[i]);
    cv::Mat temp;
    proc_img(img_name[i], src_imgs[i], temp, open_size, close_size);
    res_imgs.push_back(temp);
  }

  for (int i = 0; i < 5; i++) {
    // 显示图像
    show_img(img_name[i] + "-res", res_imgs[i]);
  }
  cv::waitKey(0);
  return 0;
}
