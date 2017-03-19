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
	int GetHeight();
	int GetWidth();
	void ShowImage();
	void GetImageRGB();
	void GetGrayImage();
	void WriteTxt_char(const char* pcName,
										 const char* pucMatrix,
										 int h,
										 int w);
private:

public:
	IplImage* grayImg;
private:
	IplImage* srcImg;
	uchar* blueComp;
	uchar* greenComp;
	uchar* redComp;
};

#endif

























