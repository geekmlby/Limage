#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#include"CDIP.h"

CDIP::CDIP()
{
	srcImg = NULL;
	blueComp = NULL;
	greenComp = NULL;
	redComp = NULL;
	grayImg = NULL;
}

CDIP::~CDIP()
{
	cvReleaseImage(&grayImg);
	delete blueComp;
	delete greenComp;
	delete redComp;
	cvReleaseImage(&srcImg);
}

void CDIP::ReadImage(char* imagePath_in)
{	
	srcImg = cvLoadImage(imagePath_in,1);
}

int CDIP::GetHeight()
{
	return srcImg -> height;
}

int CDIP::GetWidth()
{
	return srcImg -> width;
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
}

void CDIP::GetImageRGB()
{
	IplImage* blueImg;
	IplImage* greenImg;
	IplImage* redImg;
	int height,width;
	
	height = GetHeight();
	width = GetWidth();
	blueComp = new uchar[MAXHEIGHT * MAXWIDTH];
	greenComp = new uchar[MAXHEIGHT * MAXWIDTH];
	redComp = new uchar[MAXHEIGHT * MAXWIDTH];

	blueImg = cvCreateImage(cvGetSize(srcImg),8,1);
	greenImg = cvCreateImage(cvGetSize(srcImg),8,1);
	redImg = cvCreateImage(cvGetSize(srcImg),8,1);
	
	for(int i = 0;i < height;i++)
	{
		for(int j = 0;j < width;j++)
		{
			blueComp[i * blueImg -> widthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 0];
			greenComp[i * greenImg -> widthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 1];
			redComp[i * redImg -> widthStep + j] = ((uchar *)(srcImg -> imageData + i * srcImg -> widthStep))[j * srcImg -> nChannels + 2];
		}
	}

	blueImg -> imageData = (char*)blueComp;
	cvNamedWindow("blueImage",1);
	cvShowImage("blueImage",blueImg);

	greenImg -> imageData = (char*)greenComp;
	cvNamedWindow("greenImage",1);
	cvShowImage("greenImage",greenImg);

	redImg -> imageData = (char*)redComp;
	cvNamedWindow("redImage",1);
	cvShowImage("redImage",redImg);

	cvWaitKey(0);

	cvDestroyWindow("blueImage");
	cvReleaseImage(&blueImg);

	cvDestroyWindow("greenImage");
	cvReleaseImage(&greenImg);

	cvDestroyWindow("redImage");
	cvReleaseImage(&redImg);
}

void CDIP::GetGrayImage()
{
	int height,width;

	height = GetHeight();
	width = GetWidth();

	grayImg = cvCreateImage(cvGetSize(srcImg),8,1);
	for(int i = 0;i < height;i++)
	{
		for(int j = 0;j < width;j++)
		{
			*(grayImg -> imageData + i * grayImg -> widthStep + j) = *(redComp + i * grayImg -> widthStep + j) * 0.299 +
																															 *(greenComp + i * grayImg -> widthStep + j) * 0.587 +
																															 *(blueComp + i * grayImg -> widthStep + j) * 0.114;
 		}
	}
	cvNamedWindow("grayImage",1);
	cvShowImage("grayImage",grayImg);
	cvWaitKey(0);
	cvDestroyWindow("grayImage");

	cout << "The information of grayImage is:" << endl;
	cout << "The channels is:" << grayImg -> nChannels << endl;
	cout << "The depth is:" << grayImg -> depth << endl;
}




















