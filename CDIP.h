#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

#define PATHSIZE	100

class CDIP
{
public:
  CDIP();
  ~CDIP();
  int DirorFile(char* path_in);
	void Show(char* path_in);
  void ShowImage(char* imagePath_in);
  void ShowImages(char* imagesPath_in);
private:

public:
  Mat srcImage,grayImage;
private:

};

#endif

























