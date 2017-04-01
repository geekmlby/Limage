#include<stdio.h>
#include<iostream>

#include"CDIP.h"
#include"CEdgeDete.h"

using namespace std;

int main(int argc,char* argv[])
{
  CEdgeDete edgeDete;
  char path[PATHSIZE] = "/home/wangli/Limage/lena.jpg";
  //cout << "Please input path:" << endl;   
  //cin.get(path,100);
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	edgeDete.GetImageRGB();
	/*edgeDete.ShowImage("RedMat",
										 edgeDete.redMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);*/
	edgeDete.GetGrayImage();
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/grayImg_Linux.txt",
													 edgeDete.grayMat,
													 edgeDete.imgHeight,
													 edgeDete.imgWidth);
	edgeDete.Sobel();
	edgeDete.ShowImage("EdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	
  return 0;
}


























