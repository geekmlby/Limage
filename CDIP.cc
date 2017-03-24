#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#include"CDIP.h"

CDIP::CDIP()
{
	srcImg = NULL;
	blueMat = NULL;
	greenMat = NULL;
	redMat = NULL;
	grayMat = NULL;
}

CDIP::~CDIP()
{
	delete grayMat;
	delete blueMat;
	delete greenMat;
	delete redMat;
	grayMat = NULL;
	blueMat = NULL;
	greenMat = NULL;
	redMat = NULL;
	cvReleaseImage(&srcImg);
}

void CDIP::ReadImage(char* imagePath)
{	
	srcImg = cvLoadImage(imagePath,1);
	imgHeight = srcImg -> height;
	imgWidth = srcImg -> width;
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
								 		 uchar* imgMat,
								 		 int imgHeight,
								 		 int imgWidth,
										 int imgDepth,
								 		 int imgChannels)
{
	IplImage* tmpImg;
	tmpImg = cvCreateImage(cvSize(imgWidth,imgHeight),imgDepth,imgChannels);
	tmpImg -> imageData = (char*)imgMat;
	cvNamedWindow(windowName,1);
	cvShowImage(windowName,tmpImg);
	cvWaitKey(0);
	cvDestroyWindow(windowName);
	cvReleaseImage(&tmpImg);
}

void CDIP::GetImageRGB()
{
	int tmpWidthStep;

	tmpWidthStep = (0 == (srcImg -> width) % 4)?(srcImg -> width):(srcImg -> width) + (4 - ((srcImg -> width) % 4));
	blueMat = new uchar[MAXHEIGHT * MAXWIDTH];
	greenMat = new uchar[MAXHEIGHT * MAXWIDTH];
	redMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgWidth;j++)
		{
			blueMat[i * tmpWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 0];
			greenMat[i * tmpWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 1];
			redMat[i * tmpWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 2];
		}
	}
}

void CDIP::GetGrayImage()
{	
	int tmpWidthStep;

	tmpWidthStep = (0 == (srcImg -> width) % 4)?(srcImg -> width):(srcImg -> width) + (4 - ((srcImg -> width) % 4));	
	grayMat = new uchar[MAXHEIGHT * MAXWIDTH];
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgWidth;j++)
		{
			grayMat[i * tmpWidthStep + j] = redMat[i * tmpWidthStep + j] * 0.2989 +
																			greenMat[i * tmpWidthStep + j] * 0.5866 +
																			blueMat[i * tmpWidthStep + j] * 0.1145;
 		}
	}
}


















