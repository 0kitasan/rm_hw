#include "CamSim.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <cstddef>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <fstream>
#include <iostream>
#include <vector>

void FileParse(std::string filename, std::vector<std::vector<double>> &data_3D,
               uint startline) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "无法打开文件" << std::endl;
    return;
  }
  uint line_cnt = 0;
  std::string line;
  // 提取坐标
  while (std::getline(file, line)) {
    line_cnt++; // 从startline开始读取文件
    if (line_cnt >= startline) {
      std::vector<double> world_point;
      // istream分割line后，再对line进行分割，获得每个数据
      std::istringstream iss(line);
      double coord_3D;
      while (iss >> coord_3D) {
        world_point.push_back(coord_3D);
      }
      data_3D.push_back(world_point);
    }
  }
  // std::cout << "提取成功" << std::endl;
  file.close();
}

Cam::Cam(size_t width_, size_t height_,
         std::vector<std::vector<double>> Data_3D_)
    : width(width_), height(height_), Data_3D(Data_3D_),
      pointnum(Data_3D_.size()) {}

void Cam::InParam_Set() {
  InParam << 400., 0., 190., 0., 0., 400., 160., 0., 0., 0., 1., 0.;
  CamPosition << 2., 2., 2.;
  CamPose = Eigen::Quaterniond{-0.5, 0.5, 0.5, -0.5};
}

void Cam::OutParam_Calc() {
  Eigen::Matrix3d PoseMat = CamPose.toRotationMatrix();
  OutParam_transform.linear() = PoseMat;
  OutParam_transform.translation() = -PoseMat * CamPosition;
  //  std::cout << "Res1=" << OutParam_transform.matrix() << std::endl;
  // OutParam_transform.translation() = CamPosition;
  // std::cout << "Res2=" << OutParam_transform.matrix() << std::endl;
}

void Cam::Proj_Calc() {
  InParam_Set();
  OutParam_Calc();
  Eigen::Vector4d WorldCoord;
  Eigen::Vector3d CamCoord;

  for (int i = 0; i < pointnum; i++) {
    WorldCoord << Data_3D[i][0], Data_3D[i][1], Data_3D[i][2], 1.;
    CamCoord = InParam * OutParam_transform.matrix() * WorldCoord;
    // std::cout << "MatRes=" << CamCoord << std::endl;
    // int x=static_cast<int>(CamCoord[0] / CamCoord[2]);
    // int y=static_cast<int>(CamCoord[1] / CamCoord[2]);
    Data_2D_src.at<double>(0, i) = CamCoord[0] / CamCoord[2]; // 存储二维的x坐标
    Data_2D_src.at<double>(1, i) = CamCoord[1] / CamCoord[2]; // 存储二维的y坐标
    std::cout << CamCoord[0] / CamCoord[2] << " " << CamCoord[1] / CamCoord[2]
              << std::endl;
  }
  // double类型的0矩阵(opencv)
  Data_2D_dst = cv::Mat::zeros(2, pointnum, CV_64F);
}

void Cam::Img_Normalize() {
  cv::normalize(Data_2D_src.row(0), Data_2D_dst.row(0), 0, width,
                cv::NORM_MINMAX, CV_8U);
  cv::normalize(Data_2D_src.row(1), Data_2D_dst.row(1), 0, height,
                cv::NORM_MINMAX, CV_8U);
}

void Cam::Show_Img() {
  Proj_Calc();
  // Data_2D_src.copyTo(Data_2D_dst);
  Img_Normalize();
  for (int i = 0; i < pointnum; i++) {
    // int x = static_cast<int>(Data_2D_dst.at<double>(0, i));
    // int y = static_cast<int>(Data_2D_dst.at<double>(1, i));
    int x = Data_2D_dst.at<int>(0, i);
    int y = Data_2D_dst.at<int>(1, i);
    // int x0 = 800;
    // int y0 = 200;
    // cv::Point center(x0 + x, height - (y + y0));
    cv::Point center(x, height - y);
    // ocv图像原点在左上角，x正方向向右，y正方向向下
    cv::circle(Background, center, 1, cv::Scalar(0, 0, 255), 1);
  }
  cv::imshow("result", Background);
}

void Cam::Save_Img(std::string filename) { cv::imwrite(filename, Background); }