#include <assert.h>
#include <iostream>
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
  cv::inRange(img_dst, cv::Scalar(106, 65, 120), cv::Scalar(124, 255, 255),
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

void plate_extract_judge(const cv::Mat &img_input,
                         std::vector<std::vector<cv::Point>> &output_contour) {
  std::vector<std::vector<cv::Point>> all_contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(img_input, all_contours, hierarchy, cv::RETR_EXTERNAL,
                   cv::CHAIN_APPROX_NONE);
  cv::RotatedRect rotated_bound_Rect;
  double RectHeight;
  double RectWidth;
  double RectArea;
  double contour_size;
  double ratio;
  for (auto contour : all_contours) {
    rotated_bound_Rect = cv::minAreaRect(contour);
    RectHeight = rotated_bound_Rect.size.height;
    RectWidth = rotated_bound_Rect.size.width;
    RectArea = RectHeight * RectWidth;
    contour_size = cv::contourArea(contour);
    ratio = RectArea / contour_size;
    if (ratio < 1.5 && ratio > 0.5 && contour_size > 800 &&
        RectHeight / RectWidth < 5 && RectHeight / RectWidth > 0.2) {
      // std::cout << "Height=" << RectHeight << " "<< "Width=" << RectWidth <<
      // std::endl;
      output_contour.push_back(contour);
    }
  }
}

int main() {
  // 开运算与闭运算参数
  int open_size = 4, close_size = 17;

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
    // show_img(img_name[i] + "-res", res_imgs[i]);
  }

  std::vector<std::vector<std::vector<cv::Point>>> OutputContours;

  for (int i = 0; i < 5; i++) {
    std::vector<std::vector<cv::Point>> OutputContour;
    plate_extract_judge(res_imgs[i], OutputContour);
    cv::drawContours(src_imgs[i], OutputContour, -1, cv::Scalar(0, 255, 0), 2);

    std::vector<cv::Point> approxContour;
    double epsilon = 25;
    // 这里默认OutputContour容器中，只有一个轮廓，实际上可能有点问题的
    cv::approxPolyDP(OutputContour[0], approxContour, epsilon, true);
    if (approxContour.size() == 4) {
      // 绘制逼近的平行四边形
      // epsilon可调整，若取得太小，可能多边形边数>4
      cv::polylines(src_imgs[i], approxContour, true, cv::Scalar(0, 0, 255), 2);
    }

    show_img(img_name[i] + "-contour", src_imgs[i]);

    std::string output_file_name = "../output_" + img_name[i] + ".png";
    cv::imwrite(output_file_name, src_imgs[i]);
  }

  cv::waitKey(0);
  return 0;
}
