#include<stdio.h>
#include<iostream>

#include"CDIP.h"

using namespace std;

int main(int argc,char* argv[])
{
  CDIP DIP;
  char path[PATHSIZE];
  cout << "Please input path:" << endl;   
  cin.get(path,100);
  DIP.Show(path);
  return 0;
}
