#include <stdio.h>
#include <iostream>

#include "CDIP.h"
//#include "CEdgeDete.h"
//#include "CExtrFeature.h"

using namespace std;

int main(int argc,char* argv[])
{
    CDIP edgeDete;
	//char path[PATHSIZE] = "/home/wangli/Limage/img/testArray4_7.bmp";
    char path[PATHSIZE] = "/home/wangli/Limage/img/lena.bmp";
    /*cout << "Please input path:" << endl;   
    cin.get(path,100);*/
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	edgeDete.GetImageRGB();
	edgeDete.GetGrayImage();

	edgeDete.EdgeDete_Sobel(edgeDete.edgeMat,
	            		    edgeDete.puc_imgGrayMat,
						    edgeDete.imgH,
						    edgeDete.imgW,
						    150);
	edgeDete.EdgeDete_Laplace(edgeDete.edgeMat,
						 	  edgeDete.puc_imgGrayMat,
						 	  edgeDete.imgH,
						 	  edgeDete.imgW,
						 	  150);
	edgeDete.EdgeDete_Canny(edgeDete.edgeMat,
						    edgeDete.puc_imgGrayMat,
						    edgeDete.imgH,
						    edgeDete.imgW,
						    7,
						    11,
						    120,
						    50,
						    1.5);
	
  return 0;
}


























