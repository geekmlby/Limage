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
													 edgeDete.imgWidthStep);
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/GreenComp.txt",
													 edgeDete.imgGMat,
													 edgeDete.imgHeight,
													 edgeDete.imgWidthStep);
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/BlueComp.txt",
													 edgeDete.imgBMat,
													 edgeDete.imgHeight,
													 edgeDete.imgWidthStep);*/
	/*edgeDete.ShowImage("RImage",
										 edgeDete.imgRMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.ShowImage("GImage",
										 edgeDete.imgGMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.ShowImage("BImage",
										 edgeDete.imgBMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);*/
	edgeDete.GetGrayImage();
	edgeDete.WriteTxt<uchar>("/home/wangli/Limage/imgGrayMat.txt",
													 edgeDete.imgGrayMat,
													 edgeDete.imgHeight,
													 edgeDete.imgWidthStep);
	/*edgeDete.ShowImage("GrayImg",
										 edgeDete.imgGrayMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.SobelEdgeDete(edgeDete.edgeMat,
												 edgeDete.imgGrayMat,
												 edgeDete.imgHeight,
												 edgeDete.imgWidth,
												 150);
	edgeDete.ShowImage("SobelEdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.LaplaceEdgeDete(edgeDete.edgeMat,
												 	 edgeDete.imgGrayMat,
												 	 edgeDete.imgHeight,
												 	 edgeDete.imgWidth,
												 	 150);
	edgeDete.ShowImage("LaplaceEdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);*/
	edgeDete.CannyEdgeDete(edgeDete.edgeMat,
												 edgeDete.imgGrayMat,
												 edgeDete.imgHeight,
												 edgeDete.imgWidth,
												 11,
												 13,
												 200,
												 100,
												 1.5);
	edgeDete.ShowImage("GaussianEdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	//edgeDete.GaussianBlur();
	
  return 0;
}


























