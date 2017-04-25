#include<stdio.h>
#include<iostream>

#include"CDIP.h"
#include"CEdgeDete.h"

using namespace std;

int main(int argc,char* argv[])
{
  CEdgeDete edgeDete;
	//char path[PATHSIZE] = "/home/wangli/Limage/img/testArray4_4.bmp";
  char path[PATHSIZE] = "/home/wangli/Limage/img/lena_salt.bmp";
  /*cout << "Please input path:" << endl;   
  cin.get(path,100);*/
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	edgeDete.GetImageRGB();
	/*edgeDete.WriteTxt<uchar>("/home/wangli/Limage/RedComp.txt",
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
													 edgeDete.imgGrayWidthStep);*/
	edgeDete.GetGrayImage();
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/imgGrayMat.txt",
													 edgeDete.imgGrayMat,
													 edgeDete.imgHeight,
													 edgeDete.imgGrayWidthStep);
	edgeDete.ShowImage("GrayImg",
										 edgeDete.imgGrayMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	//edgeDete.SobelEdgeDete();
	edgeDete.LaplaceEdgeDete();
	edgeDete.ShowImage("EdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.GaussianBlur();
	
  return 0;
}


























