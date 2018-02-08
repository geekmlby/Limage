#include <stdio.h>
#include <iostream>

#include "CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
	CDIP edgeDete;
    char path[PATHSIZE] = "/home/wangli/Limage/img/lena.bmp";
	//char path[PATHSIZE] = "/home/wangli/Limage/img/chessboard.jpg";
    /*cout << "Please input path:" << endl;     //注：手动输入图像路径。
    cin.get(path,100);*/   
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	
	uchar* puc_GausMat = new uchar[MAXHEIGHT * MAXWIDTH];     
	edgeDete.GetGrayImage(puc_GausMat);
	edgeDete.ShowImage("GrayImage",
					   puc_GausMat,
					   edgeDete.imgH,
					   edgeDete.imgW);
	edgeDete.GausBlur(puc_GausMat,
					  edgeDete.imgH,
					  edgeDete.imgW,
					  3,
					  3,
					  1.5);
	edgeDete.ShowImage("GausImage",
					   puc_GausMat,
					   edgeDete.imgH,
					   edgeDete.imgW);

	edgeDete.EdgeDete_Canny(puc_GausMat,
							edgeDete.imgH,
							edgeDete.imgW,
							150,
							120);
	edgeDete.ShowImage("Canny",
					   puc_GausMat,
					   edgeDete.imgH,
					   edgeDete.imgW);
	delete puc_GausMat;
	puc_GausMat = NULL;

  	return 0;
}


























