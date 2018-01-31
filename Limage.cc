#include <stdio.h>
#include <iostream>

#include "CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
	CDIP edgeDete;
    char path[PATHSIZE] = "/home/wangli/Limage/img/lena.bmp";
    /*cout << "Please input path:" << endl;     //注：手动输入图像路径。
    cin.get(path,100);*/   
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();

  	return 0;
}


























