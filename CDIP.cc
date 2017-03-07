#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<cstring>

#include"CDIP.h"

CDIP::CDIP()
{

}

CDIP::~CDIP()
{

}

void CDIP::ReadImage(char* imagePath_in)
{
	IplImage* pImg;
  if ((pImg = cvLoadImage(imagePath_in, 1)) != 0)  
  {  
  	cvNamedWindow("Image", 1);  
  	cvShowImage("Image", pImg);  
  	cvWaitKey(5000);  
  	cvDestroyWindow("Image");  
  	cvReleaseImage(&pImg);  
  } 
}

int CDIP::DirorFile(char* path_in)
{
  struct stat pathBuf;
  if(0 != stat(path_in,&pathBuf))
  {
    cout << "This is not a directory or image!!" << endl;
		return -1;
  }
  else
  {
    if(S_ISREG(pathBuf.st_mode))
		{
      cout << "This is an image!" << endl;
			return 0;
		}
    if(S_ISDIR(pathBuf.st_mode))
		{
      cout << "This is a directory!" << endl;
			return 1;
		}
  }
}

void CDIP::Show(char* path_in)
{
	int fileordir;
	
	fileordir = DirorFile(path_in);
	if(0 == fileordir)
	{
		ShowImage(path_in);
	}
	else if(1 == fileordir)
	{
		ShowImages(path_in);
	}
	else
	{
	}
}

void CDIP::ShowImage(char* imagePath_in)
{
	srcImage = imread(imagePath_in,1);
  if(!srcImage.data)
  {
		cout << "There is no image!" << endl; 
  }
  else
  {
		imshow("srcImage",srcImage);
		cout << imagePath_in << endl;
		waitKey(1000);
  }
}

void CDIP::ShowImages(char* imagesPath_in)
{
  DIR* dp;
  struct dirent* dirp;
  int nameSize,pathSize;
	char imagePath[PATHSIZE];

	pathSize = strlen(imagesPath_in);
  if(NULL == (dp = opendir(imagesPath_in)))
  {
    cout << "There is no directory!" << endl;
  }
  else
  {
    while(NULL != (dirp = readdir(dp)))
    {
      nameSize = strlen(dirp -> d_name);
			if(0 == strcmp(dirp -> d_name,".") || 0 == strcmp(dirp -> d_name,".."))
			{
				continue;
			}
			else if(0 == strcmp(dirp -> d_name + (nameSize - 4),".jpg") || 0 == strcmp(dirp -> d_name + (nameSize - 4),".bmp"))
			{
				if(0 == strcmp(imagesPath_in + (pathSize - 1),"/"))
				{
					memcpy(imagePath,imagesPath_in,pathSize);
					memcpy(imagePath + pathSize,dirp -> d_name,nameSize + 1);
				}
				else
				{
					memcpy(imagePath,imagesPath_in,pathSize);
					memset(imagePath + pathSize,'/',1);
					memcpy(imagePath + pathSize + 1,dirp -> d_name,nameSize + 1);
				}
			}
			ShowImage(imagePath);
    }
		closedir(dp);
  }
}

void CDIP::GetImageRGB()
{
	//IplImage src(srcImage);
	cout << "This image's channels is: " << srcImage.channels() << endl;
}

void CDIP::GetImageYUV420()
{

}


















