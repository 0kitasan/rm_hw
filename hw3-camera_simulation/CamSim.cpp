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
  OutParam_transform.linear() = PoseMat.transpose();
  OutParam_transform.translation() = -PoseMat.transpose() * CamPosition;
  std::cout << "Trans=" << OutParam_transform.matrix() << std::endl;
  // 这里比对一下两种方法，
  // 要特别注意的是，由于旋转矩阵作用的对象和文档上似乎有所差别，需要进行转置
  Eigen::Matrix4d OutParam = Eigen::Matrix4d::Zero();
  Eigen::Matrix3d Rotate = CamPose.matrix();
  OutParam.block(0, 0, 3, 3) = Rotate.transpose();
  OutParam.block(0, 3, 3, 1) = -Rotate.transpose() * CamPosition;
  OutParam(3, 3) = 1;
  std::cout << "OutParam=" << OutParam << std::endl;
}

void Cam::Proj_Calc() {
  InParam_Set();
  OutParam_Calc();
  Eigen::Vector4d WorldCoord;
  Eigen::Vector4d CamCoord;
  Eigen::Vector3d PicCoord;
  int x, y, x1, y1;
  int x0 = 350, y0 = 100;
  for (int i = 0; i < pointnum; i++) {
    WorldCoord << Data_3D[i][0], Data_3D[i][1], Data_3D[i][2], 1.;
    CamCoord = OutParam_transform.matrix() * WorldCoord;
    PicCoord = InParam * (CamCoord / CamCoord[2]);
    // std::cout << "Cam=" << CamCoord[2] << std::endl;
    // std::cout << "Pic=" << PicCoord[2] << std::endl;
    x = static_cast<int>(PicCoord[0] / PicCoord[2]);
    y = static_cast<int>(PicCoord[1] / PicCoord[2]);
    x1 = x + x0;
    y1 = y + y0;
    cv::Point center(x1, y1);
    // cv::Point center(width - y1, height - x1);
    // 这里不知道为什么y和x都要反一下，很抽象
    // 原因：之前旋转矩阵没有转置，CamPosition不变，导致出现了某些问题，图像看起来像是另一个角度拍摄的
    cv::circle(Background, center, 1, cv::Scalar(0, 0, 255), 2);
  }
  cv::imshow("result", Background);
}

void Cam::Save_Img(std::string filename) { cv::imwrite(filename, Background); }