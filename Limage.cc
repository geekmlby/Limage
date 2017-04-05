#include<stdio.h>
#include<iostream>

#include"CDIP.h"
#include"CEdgeDete.h"

using namespace std;

int main(int argc,char* argv[])
{
	//CDIP DIP;
  CEdgeDete edgeDete;
  char path[PATHSIZE] = "/home/wangli/Limage/lena.jpg";
  //cout << "Please input path:" << endl;   
  //cin.get(path,100);
	/*DIP.ReadImage(path);
	DIP.ShowImage();
	DIP.GetImageRGB();
	DIP.ShowImage("RedMat",
							  DIP.imgRMat,
								DIP.imgHeight,
								DIP.imgWidth);
	DIP.ShowImage("GreenMat",
							  DIP.imgGMat,
								DIP.imgHeight,
								DIP.imgWidth);
	DIP.ShowImage("BlueMat",
							  DIP.imgBMat,
								DIP.imgHeight,
								DIP.imgWidth);
	DIP.GetGrayImage();
	DIP.WriteTxt<uchar>("/home/wangli/Limage/grayImg_Linux.txt",
											DIP.imgGrayMat,
											DIP.imgHeight,
											DIP.imgWidth);*/
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	edgeDete.GetImageRGB();
	/*edgeDete.ShowImage("RedMat",
							  		 edgeDete.imgRMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.ShowImage("GreenMat",
							  		 edgeDete.imgGMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	edgeDete.ShowImage("BlueMat",
							  		 edgeDete.imgBMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);*/
	edgeDete.GetGrayImage();
	/*edgeDete.WriteTxt<uchar>("/home/wangli/Limage/grayImg_Linux.txt",
													 edgeDete.imgGrayMat,
													 edgeDete.imgHeight,
													 edgeDete.imgWidth);*/
	edgeDete.Sobel();
	edgeDete.ShowImage("EdgeImage",
										 edgeDete.edgeMat,
										 edgeDete.imgHeight,
										 edgeDete.imgWidth);
	
  return 0;
}


























