#include<stdio.h>
#include<iostream>

#include"CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
  CDIP DIP;
  char path[PATHSIZE] = "/home/wangli/Limage/lena.jpg";
  /*cout << "Please input path:" << endl;   
  cin.get(path,100);*/
	DIP.ReadImage(path);
  DIP.ShowImage();
	DIP.GetImageRGB();
	/*DIP.ShowImage("blueImage",
								DIP.blueMat,
								DIP.imgHeight,
								DIP.imgWidth,
								8,
								1);
	DIP.ShowImage("greenImage",
								DIP.greenMat,
								DIP.imgHeight,
								DIP.imgWidth,
								8,
								1);
	DIP.ShowImage("redImage",
								DIP.redMat,
								DIP.imgHeight,
								DIP.imgWidth,
								8,
								1);*/
	DIP.GetGrayImage();
	DIP.ShowImage("grayImage",
								DIP.grayMat,
								DIP.imgHeight,
								DIP.imgWidth);
	DIP.WriteTxt<uchar>("/home/wangli/Limage/grayImage.txt",
								 			DIP.grayMat,
								 			DIP.imgHeight,
								 			DIP.imgWidth);
  return 0;
}


























