#include <stdio.h>
#include <iostream>

#include "CDIP.h"
#include "CEdgeDete.h"
#include "CExtrFeature.h"

using namespace std;

int main(int argc,char* argv[])
{
  CEdgeDete edgeDete;
	//char path[PATHSIZE] = "/home/wangli/Limage/img/testArray4_7.bmp";
  char path[PATHSIZE] = "/home/wangli/Limage/img/lena.bmp";
  /*cout << "Please input path:" << endl;   
  cin.get(path,100);*/
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	edgeDete.GetImageRGB();
	edgeDete.GetGrayImage();

	edgeDete.SobelEdgeDete(edgeDete.edgeMat,
												 edgeDete.imgGrayMat,
												 edgeDete.imgHeight,
												 edgeDete.imgWidth,
												 150);
	edgeDete.LaplaceEdgeDete(edgeDete.edgeMat,
												 	 edgeDete.imgGrayMat,
												 	 edgeDete.imgHeight,
												 	 edgeDete.imgWidth,
												 	 150);
	edgeDete.CannyEdgeDete(edgeDete.edgeMat,
												 edgeDete.imgGrayMat,
												 edgeDete.imgHeight,
												 edgeDete.imgWidth,
												 7,
												 11,
												 120,
												 50,
												 1.5);
	
  return 0;
}


























