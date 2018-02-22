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
	
	uchar* puc_Mat = new uchar[MAXHEIGHT * MAXWIDTH];    
	edgeDete.GetGrayImage(puc_Mat);
	edgeDete.ShowImage("GrayImage",
					   puc_Mat,
					   edgeDete.imgH,
					   edgeDete.imgW);
	/*edgeDete.GausBlur(puc_Mat,
					  edgeDete.imgH,
					  edgeDete.imgW,
					  5,
					  5,
					  1.5);
	edgeDete.ShowImage("GausImage",
					   puc_Mat,
					   edgeDete.imgH,
					   edgeDete.imgW);*/

	edgeDete.EdgeDete_Canny(puc_Mat,
							edgeDete.imgH,
							edgeDete.imgW,
							0.2,
							0.1);
	edgeDete.ShowImage("Canny_EdgeDete",
					   puc_Mat,
					   edgeDete.imgH,
					   edgeDete.imgW);
	edgeDete.SaveImage("/home/wangli/Limage/Canny.bmp",
					   puc_Mat,
					   edgeDete.imgH,
					   edgeDete.imgW);
	delete puc_Mat;
	puc_Mat = NULL;

  	return 0;
}


























