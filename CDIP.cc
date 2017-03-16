#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<exception>

#include"CDIP.h"

CDIP::CDIP()
{
	pImg = NULL;
}

CDIP::~CDIP()
{
	cvReleaseImage(&pImg);
}

void CDIP::ReadImage(char* imagePath_in)
{	
	pImg = cvLoadImage(imagePath_in,1);
}

int CDIP::GetHeight()
{
	return pImg -> height;
}

int CDIP::GetWidth()
{
	return pImg -> width;
}

void CDIP::ShowImage()
{
	if(0 != pImg)
	{
		cvNamedWindow("Image",1);
		cvShowImage("Image",pImg);
		cvWaitKey(1000);
		cvDestroyWindow("Image");
	}
}

void CDIP::GetImageRGB()
{
	IplImage* blueImg;
	IplImage* greenImg;
	IplImage* redImg;
	int h,w;
	
	h = GetHeight();
	w = GetWidth();
	blueComp = new uchar[MAXHEIGHT * MAXWIDTH];
	greenComp = new uchar[MAXHEIGHT * MAXWIDTH];
	redComp = new uchar[MAXHEIGHT * MAXWIDTH];

	blueImg = cvCreateImage(cvGetSize(pImg),8,1);
	greenImg = cvCreateImage(cvGetSize(pImg),8,1);
	redImg = cvCreateImage(cvGetSize(pImg),8,1);
	
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			blueComp[i * blueImg -> widthStep + j] = ((uchar *)(pImg -> imageData + i * pImg -> widthStep))[j * pImg -> nChannels + 0];
			greenComp[i * greenImg -> widthStep + j] = ((uchar *)(pImg -> imageData + i * pImg -> widthStep))[j * pImg -> nChannels + 1];
			redComp[i * redImg -> widthStep + j] = ((uchar *)(pImg -> imageData + i * pImg -> widthStep))[j * pImg -> nChannels + 2];
		}
	}

	blueImg -> imageData = (char*)blueComp;
	cvNamedWindow("Blue",1);
	cvShowImage("Blue",blueImg);

	greenImg -> imageData = (char*)greenComp;
	cvNamedWindow("Green",1);
	cvShowImage("Green",greenImg);

	redImg -> imageData = (char*)redComp;
	cvNamedWindow("Red",1);
	cvShowImage("Red",redImg);

	cvWaitKey(0);

	cvDestroyWindow("Blue");
	cvReleaseImage(&blueImg);

	cvDestroyWindow("Green");
	cvReleaseImage(&greenImg);

	cvDestroyWindow("Red");
	cvReleaseImage(&redImg);

	delete blueComp;
	delete greenComp;
	delete redComp;
	blueComp = NULL;
	greenComp = NULL;
	redComp = NULL;
}




















