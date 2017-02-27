#include<opencv2/opencv.hpp>
#include<vector>
#include<algorithm>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

class CDIP
{
public:
  CDIP();
  ~CDIP();
  void DirorFile(char* filePath_in);
  void ShowImage(char* filePath_in);
  void ShowImages(char* dirPath_in);
private:

public:
  Mat srcImage,grayImage;
private:

};

#endif

























