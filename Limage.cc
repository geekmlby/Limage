#include<stdio.h>
#include<iostream>

#include"CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
  CDIP DIP;
  char path[PATHSIZE] = "/home/wangli/Samples";//"/home/wangli/Samples/bike_001.jpg";
  //cout << "Please input path:" << endl;   
  //cin.get(path,100);
	//DIP.ReadImage(path);
  DIP.Show(path);
	//DIP.GetImageRGB();
  return 0;
}
