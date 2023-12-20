#include <algorithm>
#include <fstream>
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
// #include <assert.h>

void read_file_test(std::string filename, std::vector<double> &output) {
  // 打开txt文件以读取数据
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "无法打开文件" << std::endl;
    return;
  }
  // 读取数据并存储在vector中
  double value;
  while (file >> value) {
    output.push_back(value);
  }
  file.close();
}

// ReadFile(return point or vector)
// ProcData(world to camera)
// ShowRes(get img size,print res)
// 陀螺仪姿态四元数
// 0.5i+0.5j+-0.5k+-0.5
// 相机坐标(2,2,2)

void ReadFile(std::string filename, std::vector<std::vector<double>> &data_3D,
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

cv::Mat Cam_IParam(double fx, double fy, double u, double v) {
  // camera intrinsic parameters
  // 相机内参矩阵初始化
  // 400 400 190 160
  cv::Mat CIP = cv::Mat::zeros(3, 4, CV_64F);
  CIP.at<double>(0, 0) = fx;
  CIP.at<double>(1, 1) = fy;
  CIP.at<double>(0, 2) = u;
  CIP.at<double>(1, 2) = v;
  CIP.at<double>(2, 2) = 1;
  return CIP;
}

void ProcData(cv::Mat CIP, const std::vector<double> &coord_3D,
              std::vector<double> &data_2D) {
  // 世界坐标系中的点(双精度矩阵)
  cv::Mat coord_3D_MAT(4, 1, CV_64F);
  coord_3D_MAT.at<double>(0, 0) = coord_3D[0];
  coord_3D_MAT.at<double>(1, 0) = coord_3D[1];
  coord_3D_MAT.at<double>(2, 0) = coord_3D[2];
  coord_3D_MAT.at<double>(3, 0) = 1;

  // 相机坐标系中的点
  cv::Mat coord_2D_MAT = cv::Mat::ones(3, 1, CV_64F);
  coord_2D_MAT = CIP * coord_3D_MAT;
  data_2D.push_back(coord_2D_MAT.at<double>(0, 0));
  data_2D.push_back(coord_2D_MAT.at<double>(0, 1));
  data_2D.push_back(coord_2D_MAT.at<double>(0, 2));
}

cv::Mat VecToMat(const std::vector<std::vector<double>> &coord_2D_All) {
  int n = coord_2D_All.size();
  std::vector<int> X, Y;
  for (int i = 0; i < n; i++) {
    int x_temp = static_cast<int>(coord_2D_All[i][0]);
    int y_temp = static_cast<int>(coord_2D_All[i][1]);
    X.push_back(x_temp);
    Y.push_back(y_temp);
  }
}

int main() {
  cv::Mat CIP = Cam_IParam(400, 400, 190, 160);
  std::cout << CIP << std::endl;

  std::vector<std::vector<double>> data_3D;
  ReadFile("../testfile.txt", data_3D, 2);
  /*
  for (auto data : data_3D) {
    std::cout << data[0] << " " << data[1] << " " << data[2] << std::endl;
  }
  */

  std::vector<std::vector<double>> data_2D_All;
  int n = data_3D.size();
  std::cout << n << std::endl;
  for (int i; i < n; i++) {
    std::vector<double> data_2D;
    ProcData(CIP, data_3D[i], data_2D);
    // std::cout << data_2D[0] << " " << data_2D[1] << " " << data_2D[2]<<
    // std::endl;
    data_2D_All.push_back(data_2D);
  }

  return 0;
}
