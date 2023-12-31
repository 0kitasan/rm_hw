#include "CamSim.cpp"
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

int main() {
  std::string TestFileName = "../testfile.txt";
  std::string FileName = "../points.txt";
  std::vector<std::vector<double>> data_3D;
  FileParse(FileName, data_3D, 2);

  Cam cam(2000, 1000, data_3D);
  cam.Proj_Calc();
  std::string ResFile = "../result.jpg";
  cam.Save_Img(ResFile);
  cv::waitKey(0);

  return 0;
}
