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
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

int main() {
  const int board_w = 9, board_h = 6;
  const int board_n = board_w * board_h;
  cv::Size board_size(board_w, board_h);
  cv::Mat gray_img, drawn_img;
  std::vector<cv::Point2f> point_pix_pos_buf;
  std::vector<std::vector<cv::Point2f>> point_pix_pos;
  bool found;
  int successes = 0;
  cv::Size img_size;
  int cnt = 0;
  int n = 41; // chessboard数量(0-40,共41)
  for (int i = 0; i < n; i++) {
    std::string FileName = "../chess/" + std::to_string(i).append(".jpg");
    std::cout << FileName << std::endl;
    cv::Mat src0 = cv::imread(FileName);
    if (!cnt) {
      img_size.width = src0.cols;
      img_size.height = src0.rows;
    }
    found = cv::findChessboardCorners(src0, board_size, point_pix_pos_buf);
    if (found && point_pix_pos_buf.size() == board_n) {
      successes++;
      cvtColor(src0, gray_img, cv::COLOR_BGR2GRAY);
      // 对找到的角点亚像素精化
      // 它的功能为在给定的点的周围一定范围内以亚像素的精度逼近角点。
      cv::find4QuadCornerSubpix(gray_img, point_pix_pos_buf, cv::Size(5, 5));
      point_pix_pos.push_back(point_pix_pos_buf);
      drawn_img = src0.clone();
      // 画出角点，默认的似乎是彩色的
      cv::drawChessboardCorners(drawn_img, board_size, point_pix_pos_buf,
                                found);
      // 这里最好窗口名字保持一致，否则会跳出41个窗口
      cv::imshow("corners", drawn_img);
      cv::waitKey(50);
    } else
      std::cout << "\tfailed to found all chess board corners in this image "
                << std::endl;
    point_pix_pos_buf.clear();
    cnt++;
  };
  std::cout << successes << " useful chess boards" << std::endl;
  // 输出成功检测角点的chessboard的数目

  cv::Size square_size(10, 10);
  std::vector<std::vector<cv::Point3f>> point_grid_pos;
  std::vector<cv::Point3f> point_grid_pos_buf;
  std::vector<int> point_count; // 每张图的角点数目
  // 初始化，cv::Scalar::all(0)表示所有通道(3通道)的值都为0
  cv::Mat camera_matrix(3, 3, CV_32FC1, cv::Scalar::all(0));
  cv::Mat dist_coeffs(1, 5, CV_32FC1, cv::Scalar::all(0));
  // 存储畸变系数(k1,k2,k3,p1,p2)(k为径向畸变，p为切向畸变)
  std::vector<cv::Mat> rvecs;
  std::vector<cv::Mat> tvecs;
  for (int i = 0; i < successes; i++) {
    for (int j = 0; j < board_h; j++) {
      for (int k = 0; k < board_w; k++) {
        cv::Point3f pt;                // 存储所有的角点
        pt.x = k * square_size.width;  // 10pixel
        pt.y = j * square_size.height; // 10pixel
        pt.z = 0;
        point_grid_pos_buf.push_back(pt);
      }
    }
    point_grid_pos.push_back(point_grid_pos_buf);
    point_grid_pos_buf.clear();
    point_count.push_back(board_h * board_w);
  }
  std::cout << cv::calibrateCamera(point_grid_pos, point_pix_pos, img_size,
                                   camera_matrix, dist_coeffs, rvecs, tvecs)
            << std::endl;
  std::cout << camera_matrix << std::endl << dist_coeffs << std::endl;
  return 0;
}
