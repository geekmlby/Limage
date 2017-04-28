#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#include"CDIP.h"

CDIP::CDIP()
{
	imgData = NULL;
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
	srcImg = cvLoadImage(path,-1);
	imgHeight = srcImg -> height;
	imgWidth = srcImg -> width;
	imgActualWidth = (0 == (srcImg -> width) % 4)?(srcImg -> width):(srcImg -> width) + (4 - ((srcImg -> width) % 4));
	imgWidthStep = srcImg -> widthStep;
	imgChannels = srcImg -> nChannels;
	imgDepth = srcImg -> depth;
	imgSize = srcImg -> imageSize;
	imgData = (uchar*)srcImg -> imageData;
	cout << "The height of image is:" << imgHeight << endl;
	cout << "The width of image is:" << imgWidth << endl;
	cout << "The widthStep of image is:" << imgWidthStep << endl;
	cout << "The channels of image is:" << imgChannels << endl;
	cout << "The depth of image is: " << imgDepth << endl;
	cout << "The widthStep of image is: " << imgWidthStep << endl;
	cout << "The imageSize of image is: " << imgSize << endl;
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
	cvNamedWindow(windowName,0);
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
		for(int j = 0;j < imgWidthStep;j++)
		{
			imgBMat[i * imgActualWidth + j] = imgData[i * imgWidthStep + j * imgChannels + 0];
			imgGMat[i * imgActualWidth + j] = imgData[i * imgWidthStep + j * imgChannels + 1];
			imgRMat[i * imgActualWidth + j] = imgData[i * imgWidthStep + j * imgChannels + 2];
		}
	}
}

void CDIP::GetGrayImage()
{	
	double grayValueSum;
	int pos;
	imgGrayMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(3 == imgChannels)
	{
		if(NULL == imgRMat || NULL == imgGMat || NULL == imgBMat)
		{
			GetImageRGB();
		}
		else
		{
			for(int i = 0;i < imgHeight;i++)
			{
				for(int j = 0;j < imgWidthStep;j++)
				{
					grayValueSum = 2989 * imgRMat[i * imgActualWidth + j] +
										 	 	 5866 * imgGMat[i * imgActualWidth + j] +
										 	 	 1145 * imgBMat[i * imgActualWidth + j];
					imgGrayMat[i * imgActualWidth + j] = (int)(grayValueSum / 10000);
 				}
			}
		}
	}
	if(1 == imgChannels)
	{
		for(int i = 0;i < imgHeight;i++)
		{
			for(int j = 0;j < imgWidthStep;j++)
			{
				imgGrayMat[i * imgActualWidth + j] = imgData[i * imgWidthStep + j];
			}
		}
	}	
}

void CDIP::FlipMat(uchar* matrix_out,
							 		 uchar* matrix,
							 		 int height,
							 		 int width,
							 		 int eqH,
							 		 int eqW)
{
	int i,j;
	uchar* tmpMat;

	tmpMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(height <= 0 || width <= 0 || eqH > height || eqW > width)
	{
		cout << "The input parameters error!" << endl;
		return;
	}

	for(i = 0;i < eqH;i++)
	{
		memcpy(tmpMat + i * width,matrix + (eqH - (i + 1)) * width,width);
	}
	memcpy(tmpMat + eqH * width,matrix,imgHeight * width);
	for(i = imgHeight + eqH;i < imgHeight + 2 * eqH;i++)
	{
		memcpy(tmpMat + i * width,matrix + (imgHeight - (i - imgHeight - eqH + 1)) * width,width);
	}
	/*WriteTxt<uchar>("/home/wangli/Limage/UpDown.txt",
									tmpMat,
									height + 2 * eqH,
									width);*/
	
	for(i = 0;i < imgHeight + 2 * eqH;i++)
	{								
		for(j = 0;j < (width + 2 * eqW);j++)
		{
			if(j < eqW)
			{
				matrix_out[i * (width + 2 * eqW) + j] = tmpMat[i * width + (eqW - (j + 1))];
			}
			else if(j >= width + eqW)
			{
				matrix_out[i * (width + 2 * eqW) + j] = tmpMat[i * width + (width - (j - width - eqW + 1))];
			}
			else
			{
				matrix_out[i * (width + 2 * eqW) + j] = tmpMat[i * width + (j - eqW)];
			}
		}
	}
	WriteTxt<uchar>("/home/wangli/Limage/matrix_out.txt",
									matrix_out,
									height + 2 * eqH,
									width + 2 * eqW);

	delete tmpMat;
	tmpMat = NULL;
}














