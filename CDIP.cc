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
	/*cout << "The height of image is:" << imgHeight << endl;
	cout << "The width of image is:" << imgWidth << endl;
	cout << "The widthStep of image is:" << imgGrayWidthStep << endl;
	cout << "The channels of image is:" << srcImg -> nChannels << endl;*/
}

void CDIP::ShowImage()
{
	if(0 != srcImg)
	{
		cvNamedWindow("srcImage",0);
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
		for(int j = 0;j < imgGrayWidthStep;j++)
		{
			imgBMat[i * imgGrayWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 0];
			imgGMat[i * imgGrayWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 1];
			imgRMat[i * imgGrayWidthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 2];
		}
	}
}

void CDIP::GetGrayImage()
{	
	double grayValueSum;
	int pos;
	imgGrayMat = new uchar[MAXHEIGHT * MAXWIDTH];
	double r,g,b;
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgGrayWidthStep;j++)
		{
			grayValueSum = 2989 * imgRMat[i * imgGrayWidthStep + j] +
										 5866 * imgGMat[i * imgGrayWidthStep + j] +
										 1145 * imgBMat[i * imgGrayWidthStep + j];
			imgGrayMat[i * imgGrayWidthStep + j] = (int)(grayValueSum / 10000);
 		}
	}
}
















