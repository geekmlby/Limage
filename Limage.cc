#include<stdio.h>
#include<iostream>

#include"CDIP.h"
#include"CEdgeDete.h"

using namespace std;

int main(int argc,char* argv[])
{
  CEdgeDete edgeDete;
  char path[PATHSIZE] = "/home/wangli/Limage/img/testArray.bmp";
  //cout << "Please input path:" << endl;   
  //cin.get(path,100);
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	edgeDete.GetImageRGB();
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/RedComp.txt",
													 edgeDete.imgRMat,
													 edgeDete.imgHeight,
													 edgeDete.imgGrayWidthStep);
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/GreenComp.txt",
													 edgeDete.imgGMat,
													 edgeDete.imgHeight,
													 edgeDete.imgGrayWidthStep);
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/BlueComp.txt",
													 edgeDete.imgBMat,
													 edgeDete.imgHeight,
													 edgeDete.imgGrayWidthStep);
	edgeDete.GetGrayImage();
	/*edgeDete.ShowImage("GrayImg",
										 edgeDete.imgGrayMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);*/
	edgeDete.SobelEdgeDete();
	/*edgeDete.ShowImage("EdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);*/
	
  return 0;
}


























