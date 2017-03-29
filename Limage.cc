#include<stdio.h>
#include<iostream>

#include"CDIP.h"
#include"CEdgeDete.h"

using namespace std;

int main(int argc,char* argv[])
{
  CEdgeDete edgeDete;
  char path[PATHSIZE] = "/home/wangli/Limage/lena.jpg";
  //cout << "Please input path:" << endl;   
  //cin.get(path,100);
	edgeDete.ReadImage(path);
	edgeDete.ShowImage();
	
  return 0;
}


























