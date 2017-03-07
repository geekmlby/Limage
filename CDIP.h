#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

#define PATHSIZE		100
#define MAXHEIGHT		1080
#define MAXWIDTH		1920

class CDIP
{
public:
  CDIP();
  ~CDIP();
	void ReadImage(char* imagePath_in);
  int DirorFile(char* path_in);
	void Show(char* path_in);
  void ShowImage(char* imagePath_in);
  void ShowImages(char* imagesPath_in);
	void GetImageRGB();
	void GetImageYUV420();
private:

public:
  
private:
	Mat srcImage;
};

#endif

























