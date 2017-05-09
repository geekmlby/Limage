#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#include"CDIP.h"

CDIP::CDIP()
{
	srcImg = NULL;
	imgData = NULL;
	imgRMat = NULL;
	imgGMat = NULL;
	imgBMat = NULL;
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
	imgChannels = srcImg -> nChannels;
	imgDepth = srcImg -> depth;
	imgSize = srcImg -> imageSize;
	imgWidthStep = srcImg -> widthStep;
	imgData = (uchar*)srcImg -> imageData;
	cout << "***************** The Data of image,as shown below: *****************" << endl;
	cout << "The height of the image is:" << imgHeight << endl;
	cout << "The width of the image is:" << imgWidth << endl;
	cout << "The channels of the image is:" << imgChannels << endl;
	cout << "The depth of the image is: " << imgDepth << endl;
	cout << "The imageSize of the image is: " << imgSize << endl;
	cout << "The widthStep of the image is:" << imgWidthStep << endl;
	cout << "*********************************************************************" << endl;
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

/*************************************************************************
Function:Default display gray images.
*************************************************************************/
void CDIP::ShowImage(const char* windowName,
								 		 uchar* matrix,
								 		 int height,
								 		 int width,
										 int depth,
								 		 int channels)
{
	IplImage* tmpImg = NULL;
	tmpImg = cvCreateImage(cvSize(width,height),depth,channels);
	tmpImg -> imageData = (char*)matrix;
	/*cout << "+++++++++++++++++ The Data of tmpImg,as shown below: ++++++++++++++++" << endl;
	cout << "The height of the tmpImg is:" << tmpImg -> height << endl;
	cout << "The width of the tmpImg is:" << tmpImg -> width << endl;
	cout << "The channels of the tmpImg is:" << tmpImg -> nChannels<< endl;
	cout << "The depth of the tmpImg is: " << tmpImg -> depth << endl;
	cout << "The imageSize of the tmpImg is: " << tmpImg -> imageSize << endl;
	cout << "The widthStep of the tmpImg is:" << tmpImg -> widthStep << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;*/
	cvNamedWindow(windowName,0);
	cvShowImage(windowName,tmpImg);
	cvWaitKey(0);
	cvDestroyWindow(windowName);
	cvReleaseImage(&tmpImg);
}

void CDIP::GetImageRGB()
{
	imgRMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	imgGMat = new uchar[MAXHEIGHT * MAXWIDTH];
	imgBMat = new uchar[MAXHEIGHT * MAXWIDTH];
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgWidth;j++)
		{
			imgBMat[i * imgWidth + j] = imgData[i * imgWidthStep + j * imgChannels + 0];
			imgGMat[i * imgWidth + j] = imgData[i * imgWidthStep + j * imgChannels + 1];
			imgRMat[i * imgWidth + j] = imgData[i * imgWidthStep + j * imgChannels + 2];
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
				for(int j = 0;j < imgWidth;j++)
				{
					grayValueSum = 2989 * imgRMat[i * imgWidth + j] +
										 	 	 5866 * imgGMat[i * imgWidth + j] +
										 	 	 1145 * imgBMat[i * imgWidth + j];
					imgGrayMat[i * imgWidth + j] = (int)(grayValueSum / 10000);
 				}
			}
		}
	}
	if(1 == imgChannels)
	{
		for(int i = 0;i < imgHeight;i++)
		{
			for(int j = 0;j < imgWidth;j++)
			{
				imgGrayMat[i * imgWidth + j] = imgData[i * imgWidthStep + j];
			}
		}
	}	
	ShowImage("GrayImg",
						imgGrayMat,
						imgHeight,
						imgWidth);
	WriteTxt<uchar>("/home/wangli/Limage/imgGrayMat.txt",
									imgGrayMat,
									imgHeight,
									imgWidth);
}

void CDIP::FlipMat(uchar* matrix_out,
							 		 uchar* matrix,
							 		 int height,
							 		 int width,
							 		 int filterH,
							 		 int filterW)
{
	int i,j;
	int eqH,eqW;
	uchar* tmpMat;

	eqH = filterH / 2;
	eqW = filterW / 2;
	tmpMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(height <= 0 || width <= 0 || eqH > height || eqW > width)
	{
		cout << "The input parameters error!" << endl;
		return;
	}
	//Flip vertical
	for(i = 0;i < eqH;i++)
	{
		memcpy(tmpMat + i * width,matrix + (eqH - (i + 1)) * width,width);
	}
	memcpy(tmpMat + eqH * width,matrix,height * width);
	for(i = height + eqH;i < height + 2 * eqH;i++)
	{
		memcpy(tmpMat + i * width,matrix + (height - (i - height - eqH + 1)) * width,width);
	}
	//Flip horizontal
	for(i = 0;i < height + 2 * eqH;i++)
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

	/*ShowImage("FlipMatImg",
						matrix_out,
						(height + 2 * eqH),
						(width + 2 * eqW));*/

	delete tmpMat;
	tmpMat = NULL;
}














