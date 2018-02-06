#include <stdio.h>
#include <iostream>

#include "CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
	CDIP edgeDete;
    char path[PATHSIZE] = "/home/wangli/Limage/img/chessboard.jpg";
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
	edgeDete.EdgeDete_Laplace(puc_Mat,
							edgeDete.imgH,
							edgeDete.imgW,
							150);
	edgeDete.ShowImage("Edge",
					   puc_Mat,
					   edgeDete.imgH,
					   edgeDete.imgW);
	delete puc_Mat;
	puc_Mat = NULL;

  	return 0;
}


























