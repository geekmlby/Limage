#include<stdio.h>
#include<iostream>

#include"CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
  CDIP DIP;
  char path[PATHSIZE] = "/home/wangli/Samples/lena.jpg";
  /*cout << "Please input path:" << endl;   
  cin.get(path,100);*/
	DIP.ReadImage(path);
  DIP.ShowImage();
	DIP.GetImageRGB();
	DIP.GetGrayImage();
  return 0;
}
