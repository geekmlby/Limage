#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#include"CDIP.h"

CDIP::CDIP()
{
	srcImg = NULL;
	imgBMat = NULL;
	imgGMat = NULL;
	imgRMat = NULL;
	imgGrayMat = NULL;
}

CDIP::~CDIP()
{
	delete imgGrayMat;
	delete imgBMat;
	delete imgGMat;
	delete imgRMat;
	imgGrayMat = NULL;
	imgBMat = NULL;
	imgGMat = NULL;
	imgRMat = NULL;
	cvReleaseImage(&srcImg);
}

void CDIP::ReadImage(char* path)
{	
	srcImg = cvLoadImage(path,1);
	imgHeight = srcImg -> height;
	imgWidth = srcImg -> width;
	imgGrayWidthStep = (0 == (srcImg -> width) % 4)?(srcImg -> width):(srcImg -> width) + (4 - ((srcImg -> width) % 4));
}

void CDIP::ShowImage()
{
	if(0 != srcImg)
	{
		cvNamedWindow("srcImage",1);
		cvShowImage("srcImage",srcImg);
		cvWaitKey(0);
		cvDestroyWindow("srcImage");	
	}
	else
	{
		cout << "Please read an image first!" << endl;
	}
}

void CDIP::ShowImage(const char* windowName,
								 		 uchar* matrix,
								 		 int height,
								 		 int width,
										 int depth,
								 		 int channels)
{
	IplImage* tmpImg;
	tmpImg = cvCreateImage(cvSize(width,height),depth,channels);
	tmpImg -> imageData = (char*)matrix;
	cvNamedWindow(windowName,1);
	cvShowImage(windowName,tmpImg);
	cvWaitKey(0);
	cvDestroyWindow(windowName);
	cvReleaseImage(&tmpImg);
}

void CDIP::GetImageRGB()
{
	imgBMat = new uchar[MAXHEIGHT * MAXWIDTH];
	imgGMat = new uchar[MAXHEIGHT * MAXWIDTH];
	imgRMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgWidth;j++)
		{
			imgBMat[i * imgGrayWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 0];
			imgGMat[i * imgGrayWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 1];
			imgRMat[i * imgGrayWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 2];
		}
	}
}

void CDIP::GetGrayImage()
{	
	imgGrayMat = new uchar[MAXHEIGHT * MAXWIDTH];
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgWidth;j++)
		{
			imgGrayMat[i * imgGrayWidthStep + j] = imgRMat[i * imgGrayWidthStep + j] * 0.2989 +
																						 imgGMat[i * imgGrayWidthStep + j] * 0.5866 +
																						 imgBMat[i * imgGrayWidthStep + j] * 0.1145;
 		}
	}
}
















