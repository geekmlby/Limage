#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string>

#include"CDIP.h"

CDIP::CDIP()
{

}

CDIP::~CDIP()
{

}

void CDIP::DirorFile(char* path_in)
{
  struct stat pathBuf;
  if(0 != stat(path_in,&pathBuf))
  {
    cout << "This is not a directory or image!!" << endl;
  }
  else
  {
    if(S_ISREG(pathBuf.st_mode))
		{
      cout << "This is an image!" << endl;
		}
    if(S_ISDIR(pathBuf.st_mode))
		{
      cout << "This is a directory!" << endl;
		}
  }
}

void CDIP::ShowImage(char* path_in)
{
  struct stat pathBuf;
  if(0 != stat(path_in,&pathBuf))
  {
    cout << "This is not a directory or image!" << endl;
  }
  else
  {
    if(S_ISREG(pathBuf.st_mode))
    {
      cout << "This is an image!" << endl;
      srcImage = imread(path_in,1);
      if(!srcImage.data)
      {
        cout << "There is no image!" << endl; 
      }
      else
      {
					imshow("srcImage",srcImage);
					waitKey(1000);
      }
    }
    if(S_ISDIR(pathBuf.st_mode))
    {
      cout << "This is a directory!" << endl;
      ShowImages(path_in);
    }
  }
}

void CDIP::ShowImages(char* dirPath_in)
{
  DIR* dp;
  struct dirent* dirp;
  int size;
	String fileName,filePath,fullPath;

  if(NULL == (dp = opendir(dirPath_in)))
  {
    cout << "There is no directory!" << endl;
  }
  else
  {
    while(NULL != (dirp = readdir(dp)))
    {
      size = strlen(dirp -> d_name);
			if(0 == strcmp(dirp -> d_name + (size - 4),".jpg") || 0 == strcmp(dirp -> d_name + (size - 4),".bmp"))
			{
				fileName = dirp -> d_name;
				filePath = dirPath_in;
				fullPath = filePath + "/" + fileName;
				srcImage = imread(fullPath,1);
				if(!srcImage.empty())
				{
					cvtColor(srcImage,grayImage,COLOR_BGR2GRAY);
					imshow("src",srcImage);
					imshow("gray",grayImage);
					waitKey(1000);
					srcImage.release();
					grayImage.release();
				}
			}
    }
		closedir(dp);
  }
}
















