#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "CDIP.h"

CDIP::CDIP()
{
    pImg_src = NULL;	
	imgH = 0;
	imgW = 0;
	imgDepth = 0;
	imgChannel = 0;
	imgSize = 0;
	imgWidthStep = 0;
	puc_imgData = NULL;
}

CDIP::~CDIP()
{
	puc_imgData = NULL;     //puc_imgData没有使用关键字new在堆上动态创建一个对象，所以不需要delete。
	cvReleaseImage(&pImg_src);
}

void CDIP::ReadImage(char* path)
{	
	pImg_src = cvLoadImage(path,-1);
	imgH = pImg_src -> height;
	imgW = pImg_src -> width;
	actW = (0 == imgW % 4) ? imgW : imgW + (4 - imgW % 4);     //计算图像的实际宽度，非常重要。
	imgChannel = pImg_src -> nChannels;
	imgDepth = pImg_src -> depth;
	imgSize = pImg_src -> imageSize;
	imgWidthStep = pImg_src -> widthStep;
	puc_imgData = (uchar*)pImg_src -> imageData;
	cout << "***************** The Data of image,as shown below: *****************" << endl;
	cout << "The h of the image is:" << imgH << endl;
	cout << "The w of the image is:" << imgW << endl;
	cout << "The channels of the image is:" << imgChannel << endl;
	cout << "The depth of the image is: " << imgDepth << endl;
	cout << "The imageSize of the image is: " << imgSize << endl;
	cout << "The widthStep of the image is:" << imgWidthStep << endl;
	cout << "*********************************************************************" << endl;
}

void CDIP::ShowImage()
{
	if(0 != pImg_src)
	{
		cvNamedWindow("srcImage",0);
		cvShowImage("srcImage",pImg_src);
		cvWaitKey(0);
		cvDestroyWindow("srcImage");
	}
	else
	{
		cout << "Please read an image first!" << endl;
	}
}

void CDIP::ShowImage(const char* windowName,
					 uchar* Matrix,     
					 int h,
					 int w,
					 int depth,
					 int channel)
{
	IplImage* pImg_tmp = cvCreateImage(cvSize(w,h),depth,channel);
	pImg_tmp -> imageData = (char*)Matrix;
	cout << "+++++++++++++++++ The Data of tmpImg,as shown below: ++++++++++++++++" << endl;
	cout << "The h of the tmpImg is:" << pImg_tmp -> height << endl;
	cout << "The w of the tmpImg is:" << pImg_tmp -> width << endl;
	cout << "The channels of the tmpImg is:" << pImg_tmp -> nChannels<< endl;
	cout << "The depth of the tmpImg is: " << pImg_tmp -> depth << endl;
	cout << "The imageSize of the tmpImg is: " << pImg_tmp -> imageSize << endl;
	cout << "The widthStep of the tmpImg is:" << pImg_tmp -> widthStep << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cvNamedWindow(windowName,0);
	cvShowImage(windowName,pImg_tmp);
	cvWaitKey(0);
	cvDestroyWindow(windowName);
	cvReleaseImage(&pImg_tmp);
}

void CDIP::GetRGBImage(uchar* RMat,
					   uchar* GMat,
					   uchar* BMat)
{
	memset(RMat,0,MAXHEIGHT * MAXWIDTH);
	memset(GMat,0,MAXHEIGHT * MAXWIDTH);
	memset(BMat,0,MAXHEIGHT * MAXWIDTH);
	for(int i = 0;i < imgH;i++)
	{
		for(int j = 0;j < imgW;j++)
		{
			BMat[i * actW + j] = puc_imgData[i * imgWidthStep + j * imgChannel + 0];
			GMat[i * actW + j] = puc_imgData[i * imgWidthStep + j * imgChannel + 1];
			RMat[i * actW + j] = puc_imgData[i * imgWidthStep + j * imgChannel + 2];
		}
	}
}

void CDIP::GetGrayImage(uchar* GrayMat)
{	
	uchar* puc_TmpRMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	uchar* puc_TmpGMat = new uchar[MAXHEIGHT * MAXWIDTH];
	uchar* puc_TmpBMat = new uchar[MAXHEIGHT * MAXWIDTH];
	double grayValueSum;
	int pos;

	memset(GrayMat,0,MAXHEIGHT * MAXWIDTH);
	if(3 == imgChannel)
	{
		GetRGBImage(puc_TmpRMat,
					puc_TmpGMat,
					puc_TmpBMat);
		for(int i = 0;i < imgH;i++)
		{
			for(int j = 0;j < actW;j++)
			{
				grayValueSum = 2989 * puc_TmpRMat[i * actW + j] +
							   5866 * puc_TmpGMat[i * actW + j] +
							   1145 * puc_TmpBMat[i * actW + j];
				GrayMat[i * actW + j] = (int)(grayValueSum / 10000);
 			}
		}
	}
	if(1 == imgChannel)
	{
		for(int i = 0;i < imgH;i++)
		{
			for(int j = 0;j < imgW;j++)
			{
				GrayMat[i * actW + j] = puc_imgData[i * imgWidthStep + j];
			}
		}
	}	

	delete puc_TmpRMat;
	delete puc_TmpGMat;
	delete puc_TmpBMat;
	puc_TmpRMat = NULL;
	puc_TmpGMat = NULL;
	puc_TmpBMat = NULL;
}

void CDIP::SaveImage(const char* path,
					 uchar* Matrix,
					 int h,
					 int w,
					 int depth,
					 int channel)
{
	IplImage* pImg_tmp = cvCreateImage(cvSize(w,h),depth,channel);
	pImg_tmp -> imageData = (char*)Matrix;
	cvSaveImage(path,pImg_tmp);
	cvReleaseImage(&pImg_tmp);
}

void CDIP::EdgeDete_Sobel(uchar* Matrix,
						  int h,
						  int w,
						  double thre)
{
	int Gx,Gy;
	int maxV,minV;
	int* pic_GradMat = new int[MAXHEIGHT * MAXWIDTH];
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	
	maxV = 0;
	minV = 0;
	FlipMat(puc_flippedMat,
			Matrix,
			h,
			w,
			3,
			3);
	for(int i = 1;i < h + 1;i++)
	{
		for(int j = 1;j < w + 1;j++)
		{
			Gx = (-1) * puc_flippedMat[(i - 1) * (w + 2) + (j - 1)] + puc_flippedMat[(i - 1) * (w + 2) + (j + 1)] +
				 (-2) * puc_flippedMat[i * (w + 2) + (j - 1)] + 2 * puc_flippedMat[i * (w + 2) + (j + 1)] +
				 (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j - 1)] + puc_flippedMat[(i + 1) * (w + 2) + (j + 1)];
			Gy = puc_flippedMat[(i - 1) * (w + 2) + (j - 1)] + 2 * puc_flippedMat[(i - 1) * (w + 2) + j] + 
				 puc_flippedMat[(i - 1) * (w + 2) + (j + 1)] + (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j - 1)] + 
				 (-2) * puc_flippedMat[(i + 1) * (w + 2) + j] + (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j + 1)];

			pic_GradMat[i * w + j] = sqrt(SQUAREV(Gx) + SQUAREV(Gy));
			maxV = MAXV(pic_GradMat[i * w + j],maxV);
			minV = MINV(pic_GradMat[i * w + j],minV);
		}
	}
	thre = (maxV - minV) * thre + minV;
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(pic_GradMat[i * w + j] > thre)
			{
				Matrix[i * w + j] = 255;
			}
			else
			{
				Matrix[i * w + j] = 0;
			}
		}
	}

	delete pic_GradMat;
	delete puc_flippedMat;
	pic_GradMat = NULL;
	puc_flippedMat = NULL;
}

void CDIP::EdgeDete_Laplace(uchar* Matrix,
						    int h,
						    int w,
						    double thre)
{
	int maxV,minV;
	int* pic_GradMat = new int[MAXHEIGHT * MAXWIDTH];
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];

	maxV = 0;
	minV = 0;
	FlipMat(puc_flippedMat,
			Matrix,
			h,
			w,
			3,
			3);
	for(int i = 1;i < h + 1;i++)
	{
		for(int j = 1;j < w + 1;j++)
		{
			pic_GradMat[(i - 1) * w + (j - 1)] = puc_flippedMat[(i - 1) * (w + 2) + j] + puc_flippedMat[i * (w + 2) + (j - 1)] + 
											     puc_flippedMat[i * (w + 2) + (j + 1)] + puc_flippedMat[(i + 1) * (w + 2) + j] - 
											     4 * puc_flippedMat[i * (w + 2) + j];
			maxV = MAXV(pic_GradMat[(i - 1) * w + (j - 1)],maxV);
			minV = MINV(pic_GradMat[(i - 1) * w + (j - 1)],minV);
		}
	}
	thre = (maxV - minV) * thre + minV;
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(pic_GradMat[i * w + j] > thre)
			{
				Matrix[i * w + j] = 255;
			}
			else
			{
				Matrix[i * w + j] = 0;
			}
		}
	}

	delete pic_GradMat;
	delete puc_flippedMat;
	pic_GradMat = NULL;
	puc_flippedMat = NULL;
}

void CDIP::EdgeDete_Canny(uchar* Matrix,
                          int h,
                          int w,
                          double upThre,
                          double downThre)
{
	int Gx,Gy;            //注意：Gx和Gy有可能是负数。
	int maxV,minV;
	double gradDire;     //梯度方向
	double tmp1,tmp2;      
	double scale;
	bool isEdge = false;
	int* pic_GradMat = new int[MAXHEIGHT * MAXWIDTH];
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	int* pic_flippedMat = new int[MAXHEIGHT * MAXWIDTH];

	if(upThre < downThre)
	{
		cout << "The input data is wrong!upThre is smaller than downThre!" << endl;
		return;
	}

	maxV = 0;
	minV = 0;
	FlipMat(puc_flippedMat,
			Matrix,
			h,
			w,
			3,
			3);
	for(int i = 1;i < h + 1;i++)
	{
		for(int j = 1;j < w + 1;j++)
		{
			Gx = (-1) * puc_flippedMat[(i - 1) * (w + 2) + (j - 1)] + puc_flippedMat[(i - 1) * (w + 2) + (j + 1)] +
				 (-2) * puc_flippedMat[i * (w + 2) + (j - 1)] + 2 * puc_flippedMat[i * (w + 2) + (j + 1)] +
				 (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j - 1)] + puc_flippedMat[(i + 1) * (w + 2) + (j + 1)];
			Gy = puc_flippedMat[(i - 1) * (w + 2) + (j - 1)] + 2 * puc_flippedMat[(i - 1) * (w + 2) + j] + 
				 puc_flippedMat[(i - 1) * (w + 2) + (j + 1)] + (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j - 1)] + 
				 (-2) * puc_flippedMat[(i + 1) * (w + 2) + j] + (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j + 1)];
			pic_GradMat[(i - 1) * w + (j - 1)] = sqrt(SQUAREV(Gx) + SQUAREV(Gy));
			maxV = MAXV(pic_GradMat[(i - 1) * w + (j - 1)],maxV);
			minV = MINV(pic_GradMat[(i - 1) * w + (j - 1)],minV);
		}
	}

	FlipMat(pic_flippedMat,
			pic_GradMat,
			h,
			w,
			3,
			3);
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			Gx = puc_flippedMat[i * (w + 2) + (j + 2)] - puc_flippedMat[i * (w + 2) + j];
			Gy = puc_flippedMat[(i + 2) * (w + 2) + j] - puc_flippedMat[i * (w + 2) + j];
			gradDire = atan2(Gy,Gx) /PI * 180;
			gradDire = gradDire >= 0 ? gradDire : gradDire + 180;
			if(gradDire == 0 || gradDire == 180)     //非极大值抑制
			{
				tmp1 = puc_flippedMat[(i + 1) * (w + 2) + j + 2];
				tmp2 = puc_flippedMat[(i + 1) * (w + 2) + j];
			}
			if(gradDire > 0 && gradDire < 45)     
			{
				scale = tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(puc_flippedMat[i * (w + 2) + j + 2] - puc_flippedMat[(i + 1) * (w + 2) + j + 2])) * scale 
					   + puc_flippedMat[(i + 1) * (w + 2) + j + 2]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j] - puc_flippedMat[(i + 1) * (w + 2) + j])) * scale 
					   + puc_flippedMat[(i + 1) * (w + 2) + j]);
			}
			if(gradDire >= 45 && gradDire < 90)
			{
				scale = 1 / tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(puc_flippedMat[i * (w + 2) + j + 2] - puc_flippedMat[i * (w + 2) + j + 1])) * scale 
					   + puc_flippedMat[i * (w + 2) + j + 1]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j + 1] - puc_flippedMat[(i + 2) * (w + 2) + j])) * scale 
					   + puc_flippedMat[(i + 2) * (w + 2) + j]);
			}
			if(gradDire == 90)
			{
				tmp1 = puc_flippedMat[i * (w + 2) + j + 1];
				tmp2 = puc_flippedMat[(i + 2) * (w + 2) + j + 1];
			}
			if(gradDire > 90 && gradDire < 135)
			{
				scale = -1 / tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(puc_flippedMat[i * (w + 2) + j + 1] - puc_flippedMat[i * (w + 2) + j])) * scale 
					   + puc_flippedMat[i * (w + 2) + j]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j + 2] - puc_flippedMat[(i + 2) * (w + 2) + j])) * scale 
					   + puc_flippedMat[(i + 2) * (w + 2) + j]);
			}
			if(gradDire >= 135 && gradDire < 180)
			{
				scale = -tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(puc_flippedMat[(i + 1) * (w + 2) + j] - puc_flippedMat[i * (w + 2) + j])) * scale 
					   + puc_flippedMat[i * (w + 2) + j]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j + 2] - puc_flippedMat[(i + 2) * (w + 2) + j + 1])) * scale 
					   + puc_flippedMat[(i + 2) * (w + 2) + j + 1]);
			}
			if(tmp1 > pic_GradMat[i * w + j] || tmp2 > pic_GradMat[i * w + j])
			{
				pic_GradMat[i * w + j] = 0;
			}
		}
	}

	downThre = (maxV - minV) * downThre + minV;
	upThre = (maxV - minV) * upThre + minV;
	FlipMat(pic_flippedMat,
			pic_GradMat,
			h,
			w,
			3,
			3);
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(pic_GradMat[i * w + j] > upThre)
			{
				Matrix[i * w + j] = 255;
			}
			else if(pic_GradMat[i * w + j] <= upThre && pic_GradMat[i * w + j] > downThre)
			{
				isEdge = false;
				for(int k = i;k < i + 2;k++)
				{
					for(int l = j;l < j + 2;l++)
					{
							if(pic_flippedMat[k * (w + 2) + l] > upThre)
							{
								isEdge = true;
								Matrix[i * w + j] = 255;
								break;
							}
					}
					if(true == isEdge)
					{
						break;
					}
				}
				if(false == isEdge)
				{
					Matrix[i * w + j] = 0;
				}
			}
			else
			{
				Matrix[i * w + j] = 0;
			}
		}
	}

	delete pic_GradMat;
	delete puc_flippedMat;
	delete pic_flippedMat;
	pic_GradMat = NULL;
	puc_flippedMat = NULL;
	pic_flippedMat = NULL;
}

void CDIP::GausBlur(uchar* Matrix,
					int h,
					int w,
					int filH,
					int filW,
					double sigma)
{
	int eqH,eqW;
	double* WeiMat = new double[MAXLENGTH];
	double sum;

	eqH = filH / 2;
	eqW = filW / 2;
	for(int x = (-1 * eqH);x < (eqH + 1);x++)
	{
		for(int y = (-1 * eqW);y < (eqW + 1);y++)
		{
			WeiMat[(x + eqH) * filW + (y + eqW)] = 
            exp(-1 * (SQUAREV(x) + SQUAREV(y)) / (2 * SQUAREV(sigma))) / (2 * PI * SQUAREV(sigma));
			sum = sum + WeiMat[(x + eqH) * filW + (y + eqW)];
		}
	}
	for(int i = 0;i < (filH * filW);i++)
	{
		WeiMat[i] = WeiMat[i] / sum;
	}
	CalConv(Matrix,
			WeiMat,
			h,
			w,
			filH,
			filW);
	
	delete WeiMat;
	WeiMat = NULL;
}

void CDIP::CalConv(uchar* Matrix,     //因为计算卷积的时候，有可能输出负值，uchar数组中的数据会出现错误，所以这个函数要慎用。
				   double* Wei,       //Wei都是正值的时候，可以用这个函数。
                   int h,
                   int w,
                   int filH,
                   int filW)
{
	double tmp = 0.0;
	int eqH,eqW;
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	uchar* WinMat = new uchar[MAXLENGTH];
	eqH = filH / 2;
	eqW = filW / 2;

	FlipMat(puc_flippedMat,
			Matrix,
			h,
			w,
			filH,
			filW);
	for(int i = eqH;i < h + eqH;i++)
	{
		for(int j = eqW;j < w + eqW;j++)
		{
			for(int x = (-1 * eqH);x < (eqH + 1);x++)
			{
				for(int y = (-1 * eqW);y < (eqW + 1);y++)
				{
					WinMat[(x + eqH) * filW + (y + eqW)] = puc_flippedMat[(i + x) * (w + 2 * eqW) + (j + y)];
				}
			}	
			for(int k = 0;k < (filH * filW);k++)
			{
				tmp += (WinMat[k] * Wei[k]);
				WinMat[k] = 0;
			}	
			Matrix[(i - eqH) * w + (j - eqW)] = tmp;
			tmp = 0;
		}
	}

	delete puc_flippedMat;
	delete WinMat;
	puc_flippedMat = NULL;
	WinMat = NULL;		
}



































