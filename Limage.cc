#include<stdio.h>
#include<iostream>

#include"CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
  CDIP DIP;
  char path[100];
  cout << "Please input path:" << endl;   //path = "/home/wangli/Pic/bike_001.bmp"
  cin.get(path,100);
	//DIP.DirorFile(path);
  DIP.ShowImage(path);
  return 0;
}
