#include "opencv2/core/hal/interface.h"
#include <eigen3/Eigen/Dense>
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

void FileParse(std::string filename, std::vector<std::vector<double>> &data_3D,
               uint startline);

class Cam {
private:
  Eigen::Matrix<double, 3, 4> InParam; // intrinsic parameters of camera
  Eigen::Vector3d CamPosition;         // 相机位置坐标(2,2,2)
  Eigen::Quaterniond CamPose; // 相机姿态四元数 -0.5 + 0.5i + 0.5j + -0.5k
  Eigen::Transform<double, 3, Eigen::Affine> OutParam_transform;
  // 创建仿射变换(Affine)矩阵，3是变换的维度而不是矩阵大小
  size_t width, height, pointnum;
  cv::Mat Background = cv::Mat::zeros(height, width, CV_8UC3);
  std::vector<std::vector<double>> Data_3D; // 初始化时设定
  void InParam_Set();
  void OutParam_Calc();

public:
  Cam(size_t width_, size_t height_, std::vector<std::vector<double>> Data_3D_);
  void Proj_Calc();
  // void Show_Img();
  void Save_Img(std::string filename);
};