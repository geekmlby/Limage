#include <stdio.h>
#include <iostream>

#include "CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
	CDIP edgeDete;
    char path[PATHSIZE] = "/home/wangli/Limage/img/lena.bmp";
    //char path[PATHSIZE] = "/home/wangli/Limage/img/lena_salt.bmp";
	//char path[PATHSIZE] = "/home/wangli/Limage/img/chessboard.jpg";
    /*cout << "Please input path:" << endl;     //注：手动输入图像路径。
    cin.get(path,100);*/   
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	
	uchar* puc_Mat = new uchar[MAXHEIGHT * MAXWIDTH]; 
	uchar* puc_Mat2 = new uchar[MAXHEIGHT * MAXWIDTH];    
	edgeDete.GetGrayImage(puc_Mat);
	edgeDete.ShowImage("GrayImage",
					   puc_Mat,
					   edgeDete.imgH,
					   edgeDete.imgW);

	edgeDete.Stretch(puc_Mat2,
					 puc_Mat,
					 edgeDete.imgH,
					 edgeDete.imgW,
					 30);
	edgeDete.ShowImage("Stretch",
					   puc_Mat2,
					   edgeDete.imgH,
					   edgeDete.imgW);
	edgeDete.SaveImage("/home/wangli/Limage/Stretch.bmp",
					   puc_Mat2,
					   edgeDete.imgH,
					   edgeDete.imgW);
	delete puc_Mat;
	delete puc_Mat2;
	puc_Mat = NULL;
	puc_Mat2 = NULL;

  	return 0;
}


























