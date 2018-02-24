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

int CDIP::ReadImage(char* path)
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

	return 1;
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
	int* pi_GradMat = new int[MAXHEIGHT * MAXWIDTH];
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(!Matrix || thre < 0 || thre > 1)
	{
		cout << "The input data is wrong!" << endl;
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

			pi_GradMat[i * w + j] = sqrt(SQUAREV(Gx) + SQUAREV(Gy));
			maxV = MAXV(pi_GradMat[i * w + j],maxV);
			minV = MINV(pi_GradMat[i * w + j],minV);
		}
	}
	thre = (maxV - minV) * thre + minV;
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(pi_GradMat[i * w + j] > thre)
			{
				Matrix[i * w + j] = 255;
			}
			else
			{
				Matrix[i * w + j] = 0;
			}
		}
	}

	delete pi_GradMat;
	delete puc_flippedMat;
	pi_GradMat = NULL;
	puc_flippedMat = NULL;
}

void CDIP::EdgeDete_Laplace(uchar* Matrix,
						    int h,
						    int w,
						    double thre)
{
	int maxV,minV;
	int* pi_GradMat = new int[MAXHEIGHT * MAXWIDTH];
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(!Matrix || thre < 0 || thre > 1)
	{
		cout << "The input data is wrong!" << endl;
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
			pi_GradMat[(i - 1) * w + (j - 1)] = puc_flippedMat[(i - 1) * (w + 2) + j] + puc_flippedMat[i * (w + 2) + (j - 1)] + 
											     puc_flippedMat[i * (w + 2) + (j + 1)] + puc_flippedMat[(i + 1) * (w + 2) + j] - 
											     4 * puc_flippedMat[i * (w + 2) + j];
			maxV = MAXV(pi_GradMat[(i - 1) * w + (j - 1)],maxV);
			minV = MINV(pi_GradMat[(i - 1) * w + (j - 1)],minV);
		}
	}
	thre = (maxV - minV) * thre + minV;
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(pi_GradMat[i * w + j] > thre)
			{
				Matrix[i * w + j] = 255;
			}
			else
			{
				Matrix[i * w + j] = 0;
			}
		}
	}

	delete pi_GradMat;
	delete puc_flippedMat;
	pi_GradMat = NULL;
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
	double gradDire;      //梯度方向
	double tmp1,tmp2;      
	double scale;
	bool isEdge = false;
	int* pi_GradMat = new int[MAXHEIGHT * MAXWIDTH];
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	int* pi_flippedMat = new int[MAXHEIGHT * MAXWIDTH];

	if(!Matrix || upThre < downThre || downThre < 0 || upThre > 1)
	{
		cout << "The input data is wrong!" << endl;
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
			pi_GradMat[(i - 1) * w + (j - 1)] = sqrt(SQUAREV(Gx) + SQUAREV(Gy));
			maxV = MAXV(pi_GradMat[(i - 1) * w + (j - 1)],maxV);
			minV = MINV(pi_GradMat[(i - 1) * w + (j - 1)],minV);
		}
	}

	FlipMat(pi_flippedMat,
			pi_GradMat,
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
				tmp1 = pi_flippedMat[(i + 1) * (w + 2) + j + 2];
				tmp2 = pi_flippedMat[(i + 1) * (w + 2) + j];
			}
			if(gradDire > 0 && gradDire < 45)     
			{
				scale = tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(pi_flippedMat[i * (w + 2) + j + 2] - pi_flippedMat[(i + 1) * (w + 2) + j + 2])) * scale 
					   + pi_flippedMat[(i + 1) * (w + 2) + j + 2]);
				tmp2 = (double)(((double)(pi_flippedMat[(i + 2) * (w + 2) + j] - pi_flippedMat[(i + 1) * (w + 2) + j])) * scale 
					   + pi_flippedMat[(i + 1) * (w + 2) + j]);
			}
			if(gradDire >= 45 && gradDire < 90)
			{
				scale = 1 / tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(pi_flippedMat[i * (w + 2) + j + 2] - pi_flippedMat[i * (w + 2) + j + 1])) * scale 
					   + pi_flippedMat[i * (w + 2) + j + 1]);
				tmp2 = (double)(((double)(pi_flippedMat[(i + 2) * (w + 2) + j + 1] - pi_flippedMat[(i + 2) * (w + 2) + j])) * scale 
					   + pi_flippedMat[(i + 2) * (w + 2) + j]);
			}
			if(gradDire == 90)
			{
				tmp1 = pi_flippedMat[i * (w + 2) + j + 1];
				tmp2 = pi_flippedMat[(i + 2) * (w + 2) + j + 1];
			}
			if(gradDire > 90 && gradDire < 135)
			{
				scale = -1 / tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(pi_flippedMat[i * (w + 2) + j + 1] - pi_flippedMat[i * (w + 2) + j])) * scale 
					   + pi_flippedMat[i * (w + 2) + j]);
				tmp2 = (double)(((double)(pi_flippedMat[(i + 2) * (w + 2) + j + 2] - pi_flippedMat[(i + 2) * (w + 2) + j])) * scale 
					   + pi_flippedMat[(i + 2) * (w + 2) + j]);
			}
			if(gradDire >= 135 && gradDire < 180)
			{
				scale = -tan(gradDire / 180 * PI);
				tmp1 = (double)(((double)(pi_flippedMat[(i + 1) * (w + 2) + j] - pi_flippedMat[i * (w + 2) + j])) * scale 
					   + pi_flippedMat[i * (w + 2) + j]);
				tmp2 = (double)(((double)(pi_flippedMat[(i + 2) * (w + 2) + j + 2] - pi_flippedMat[(i + 2) * (w + 2) + j + 1])) * scale 
					   + pi_flippedMat[(i + 2) * (w + 2) + j + 1]);
			}
			if(tmp1 > pi_GradMat[i * w + j] || tmp2 > pi_GradMat[i * w + j])
			{
				pi_GradMat[i * w + j] = 0;
			}
		}
	}

	downThre = (maxV - minV) * downThre + minV;
	upThre = (maxV - minV) * upThre + minV;
	FlipMat(pi_flippedMat,
			pi_GradMat,
			h,
			w,
			3,
			3);
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(pi_GradMat[i * w + j] > upThre)
			{
				Matrix[i * w + j] = 255;
			}
			else if(pi_GradMat[i * w + j] <= upThre && pi_GradMat[i * w + j] > downThre)
			{
				isEdge = false;
				for(int k = i;k < i + 2;k++)
				{
					for(int l = j;l < j + 2;l++)
					{
							if(pi_flippedMat[k * (w + 2) + l] > upThre)
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

	delete pi_GradMat;
	delete puc_flippedMat;
	delete pi_flippedMat;
	pi_GradMat = NULL;
	puc_flippedMat = NULL;
	pi_flippedMat = NULL;
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
	if(!Matrix || h <= 0 || w <= 0 || eqH > h || eqW > w)
	{
		cout << "The input parameters error!" << endl;
		return;
	}

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

	FlipMat(puc_flippedMat,           //翻转函数会判断filH，filW和h，w的大小关系，因此不用单独判断。
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

void CDIP::Histeq(uchar* Matrix,
				  int h,
				  int w)
{
	if (!Matrix || 0 == h || 0 == w)
	{
		cout << "The input data is wrong!" << endl;
		return;
	}

	int index = 0;
	int *pi_HistOne = new int[256];

	memset(pi_HistOne,
		   0,
		   sizeof(int) * 256);
	for (int i = 0;i < h * w;i++)
	{
		index = Matrix[i];
		pi_HistOne[index]++;
	}
	for (int i = 1;i < 256;i++)
	{
		pi_HistOne[i] = pi_HistOne[i-1] + pi_HistOne[i];
	}
	for (int i = 0;i < 256;i++)
	{
		pi_HistOne[i] = ((double)(255 * pi_HistOne[i])) / (h * w);
	}
	for (int i = 0;i < h * w;i++)
	{
		index = Matrix[i];
		Matrix[i] = (uchar)pi_HistOne[index];
	}

	delete pi_HistOne;
	pi_HistOne = NULL;
}

void CDIP::MeanFilter(uchar* Matrix,
				 	  int h,
					  int w,
					  int filH,
					  int filW)
{
	int eqH,eqW;
	int totalH,totalW;             //补偿后的总行数，总列数。
	int filLen;
	uchar* puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	double* pd_ColSum = new double[MAXHEIGHT * MAXWIDTH];
	double* pd_InteMat = new double[MAXHEIGHT * MAXWIDTH];

	eqH = filH / 2;
	eqW = filW / 2;
	totalH = h + (filH / 2) * 2;
	totalW = w + (filW / 2) * 2;
	filLen = filH * filW;

	if(!Matrix || 0 == h || 0 == w || eqH > h || eqW > w)
	{
		cout << "The input parameters error!" << endl;
		return;
	}

	//此时的puc_flippedMat的大小是翻转后，又补了一行一列，先将其全部赋值为0。因此不能使用FlipMat函数。
	memset(puc_flippedMat,0,sizeof(uchar) * ((totalH + 1) * (totalW + 1)));
	//下列代码的作用是把Matrix的内容复制到puc_flippedMat中	
	for (int i = eqH + 1;i < h + eqH + 1;i++)
	{
		memcpy(puc_flippedMat + (i * (totalW + 1)) + eqW + 1,Matrix + (i - eqH - 1) * w,sizeof(uchar) * w);
	}
	//下列代码进行其他行翻转
	for (int i = 0;i < eqH + 1;i++)
	{
		memcpy(puc_flippedMat + (i + 1) * (totalW + 1) + eqW + 1,
			   puc_flippedMat + (((eqH + 1 - 1) + (eqH - i)) * (totalW + 1)) + eqW + 1,
			   sizeof(uchar) * w);
	}

	for (int i = h + eqH + 1;i < totalH + 1;i++)
	{
		memcpy(puc_flippedMat + i* (totalW + 1) + eqW + 1,
			   puc_flippedMat + (2 * (h + eqH) - i +1) * (totalW + 1) + eqW + 1,
			   sizeof(uchar) * w);
	}	
	//下列代码进行列翻转
	for (int i = 1;i < totalH + 1;i++)
	{
		for (int j = 1;j <= eqW + 1;j++)
		{
			puc_flippedMat[i * (totalW + 1) + j] = puc_flippedMat[i * (totalW + 1) + (2 * eqW) + 1 - j];
		}

		for (int j = 1 + eqW + w;j < totalW + 1;j++)
		{
			puc_flippedMat[i * (totalW + 1) + j] = puc_flippedMat[i * (totalW + 1) + (2 * (w + eqW) + 1) - j];
		}
	}

	//下列代码开始进行积分图的运算,因为puc_flippedMat翻转后，又补了一行一列，所以不能使用InteImg函数。
	//对第一行进行积分
	for(int i = 1;i < totalW + 1;i++)
	{  
		pd_ColSum[i] = puc_flippedMat[totalW + 1 + i];  
		pd_InteMat[totalW + 1 + i] = puc_flippedMat[totalW + 1 + i];  
		if(i > 1)
		{  
			pd_InteMat[totalW + 1 + i] += pd_InteMat[totalW + i];  
		}  
	}  

	for (int i = 2;i < totalH + 1;i++)
	{  
		int offset = i * (totalW + 1);  
		//对第一列进行积分 
		pd_ColSum[1] += puc_flippedMat[offset + 1];  
		pd_InteMat[offset + 1] = pd_ColSum[1];  
		//对第一行和第一列之外的行和列进行积分 
		for(int j = 2;j < totalW + 1;j++)
		{  
			pd_ColSum[j] += puc_flippedMat[offset + j];  
			pd_InteMat[offset + j] = pd_InteMat[offset + j - 1] + pd_ColSum[j];   
		}  
	} 

	for (int i = 0;i < h;i++)
	{
		for (int j = 0;j < w;j++)
		{
			Matrix[i * w + j] = (uchar)((pd_InteMat[(i + 2 * eqH + 1) * (totalW + 1) + (j + 2 * eqW + 1)]
								- pd_InteMat[(i + 2 * eqH + 1) * (totalW + 1) + j]
								- pd_InteMat[i * (totalW + 1) + (j + 2 * eqW + 1)]
								+ pd_InteMat[i * (totalW + 1) + j])
								/ filLen);
		}
	}

	delete puc_flippedMat;
	delete pd_ColSum;
	delete pd_InteMat;
	puc_flippedMat = NULL;
	pd_InteMat = NULL;
	pd_ColSum = NULL;
}

void CDIP::InteImg(double* Mat_out,
				   uchar* Matrix,
				   int h,
				   int w)
{
	if (!Matrix || 0 == h || 0 == w)
	{
		cout << "The input data is wrong!" << endl;
		return;
	}

	double* pd_ColSum = new double[MAXHEIGHT * MAXWIDTH]; 

	for(int i = 0;i < w;i++)
	{  
		pd_ColSum[i] = Matrix[i];  
		Mat_out[i] = Matrix[i];  
		if(i > 0)
		{  
			Mat_out[i] += Mat_out[i - 1];  
		}  
	}  
	for (int i = 1;i < h;i++)
	{  
		int offset = i * w;    //偏移量
		//对第一列进行积分 
		pd_ColSum[0] += Matrix[offset];  
		Mat_out[offset] = pd_ColSum[0];  
		//对第一行和第一列之外的行和列进行积分 
		for(int j = 1;j < w;j++)
		{  
			pd_ColSum[j] += Matrix[offset + j];  
			Mat_out[offset + j] = Mat_out[offset + j - 1] + pd_ColSum[j];   
		}  
	}  

	delete pd_ColSum;
	pd_ColSum = NULL;
}

void CDIP::BilinearInte(uchar* Mat_out,
						uchar* Matrix,
						int h,
						int w,
						int h2,
						int w2)
{
	if (!Matrix || 0 == h || 0 == w || 0 == h2 || 0 == w2)
	{
		cout << "The input data is wrong!" << endl;
		return;
	}

	int A = 0,B = 0,C = 0,D = 0,E = 0,F = 0,G = 0;
	int i1 = 0,j1 = 0;
	int i2 = 0,j2 = 0;
	int i = 0,j = 0;
	int hRadio = 0;
	int wRadio = 0;
	int iRadio = 0;
	int jRadio = 0;

	hRadio = 64 * (h - 1) / (h2 - 1);
	wRadio = 64 * (w - 1) / (w2 - 1);
	for (i2 = 0;i2 < h2;i2++)
	{
		for (j2 = 0;j2 < w2;j2++)
		{
			i = i2 * hRadio;
			j = j2 * wRadio;
			i1 = i >> 6;
			j1 = j >> 6;
			iRadio = i - (i1 << 6);
			jRadio = j - (j1 << 6);
			A = Matrix[i1 * w + j1];
			B = Matrix[i1 * w + j1 +1];
			C = Matrix[(i1 + 1) * w + j1];
			D = Matrix[(i1 + 1) * w + j1 + 1];
			E = (B - A) * jRadio + (A << 6);
			F = (D - C) * jRadio + (C << 6);
			G = (F - E) * iRadio + (E << 6);
			Mat_out[i2 * w2 + j2] = (uchar)(G >> 12);
		}
	}
}

void CDIP::Stretch(uchar* Mat_out,           //图像延展 
				   uchar* Matrix,
				   int h,
				   int w,
				   double ang)
{
	if (!Matrix || 0 == h || 0 == w || ang > 90.0)
	{
		cout << "The input data is wrong!" << endl;
		return;
	}

	int i1 = 0,j1 = 0,i2 = 0,j2 = 0,i = 0,j = 0;
	int A = 0,B = 0,C = 0;
	int halfH = 0;
	int wRadio = 0;
	int tanV = round(tan(ang / 180 * PI) * 1024);

	memset(Mat_out,0,sizeof(uchar) * (h * w));
	if (h % 2 == 0)
	{
		halfH = (h - 1) / 2;
	}
	else
	{
		halfH = h / 2;
	}
	//下列代码，采用了插值法，效果已实现。
	for (i2 = 0;i2 < h;i2++)
	{
		for (j2 = 0;j2 < w;j2++)
		{
			i1 = i2;
			if (i2 <= halfH)
			{
				j = (j2 << 10) - (halfH - i2) * tanV;
			} 
			if(i2 > halfH)
			{
				j = (j2 << 10) + (i2 - halfH) * tanV;
			}
			j1 = j >> 10;
			if (j1 >= 0 && j1 < w)
			{
				wRadio = j - (j1 << 10);
				A = Matrix[i1 * w + j1];
				B = Matrix[i1 * w + j1 + 1];
				C = (B - A) * wRadio + (A << 10);
				Mat_out[i2 * w + j2] = (uchar)A;
			}
			else if (j1 < 0)
			{
				Mat_out[i2 * w + j2] = Matrix[i1 * w];
			} 
			else
			{
				Mat_out[i2 * w + j2] = Matrix[(i1 + 1) * w - 1];
			}
		}
	}
}

void CDIP::Rotate(uchar* Mat_out,
				  uchar* Matrix,
				  int h,
				  int w,              
				  double ang)
{
	if (!Matrix || 0 == h || 0 == w || ang > 90.0 || ang < -90.0)
	{
		cout << "The input data is wrong!" << endl;
		return;
	}

	int i1 = 0,j1 = 0,i2 = 0,j2 = 0,i = 0,j = 0,k = 0;
	int x1 = 0,y1 = 0,x2 = 0,y2 = 0;
	int sinV = 0,cosV = 0;
	int hRadio = 0,wRadio = 0;             //定义这两个int型变量，主要是为了插值运算时用。
	int halfH = 0,halfW = 0;
	int A = 0,B = 0,C = 0,D = 0,E = 0,F = 0,G = 0;
	int count = 0;
	int j2EqStart = 0,j2EqEnd = 0;
	int Edge[MAXWIDTH] = {0};              //用这个数组来记录pucY2的边界值。

	if (ang >= 0)
	{
		sinV = round(sin(ang / 180 * PI) * 1024);
		cosV = round(cos(ang / 180 * PI) * 1024);
	} 
	else
	{
		sinV = -round(sin(-ang / 180 * PI) * 1024);
		cosV = round(cos(ang / 180 * PI) * 1024);
	}
	//下列代码求直角坐标的原点。
	if (h % 2 == 0)
	{
		halfH = (h - 1) / 2;
	}
	else
	{
		halfH = h / 2;
	}
	if (w % 2 == 0)
	{
		halfW = (w - 1) / 2;
	} 
	else
	{
		halfW = w / 2;
	}

	memset(Mat_out,0,sizeof(uchar) * (h * w));
	for(i2 = 0; i2 < h; i2++)
	{
		for(j2 = 0; j2 < w; j2++)
		{
			y2 = halfH - i2;
			x2 = j2 - halfW;
			x1 = x2 * cosV - y2 * sinV;
			y1 = x2 * sinV + y2 * cosV;
			//下列代码用插值进行图像翻转
			i = (halfH << 10) - y1;
			j = x1 + (halfW << 10);			
			i1 = i >> 10;
			j1 = j >> 10;
			hRadio = i - (i1 << 10);
			wRadio = j - (j1 << 10);
			A = Matrix[i1 * w + j1];
			B = Matrix[i1 * w + j1 + 1];
			C = Matrix[(i1 + 1) * w + j1];
			D = Matrix[(i1 + 1) * w + j1 + 1];
			E = (B - A) * wRadio + (A << 10);
			F = (D - C) * wRadio + (C << 10);
			G = (F - E) * hRadio + (E << 10);
			if (i1 >= 0 && i1 < h - 1 && j1 >= 0 && j1 < w - 1)
			{
				Mat_out[i2 * w + j2] = (uchar)(G >> 20);
				Edge[count] = j2;
				count++;
			}
		}
		j2EqStart = Edge[0];
		j2EqEnd = Edge[count - 1];	
		for (k = 0;k< j2EqStart;k++)
		{
			Mat_out[i2 * w + k] = Mat_out[i2 * w + j2EqStart];    // 左角 赋值
		} 
		for (k = j2EqEnd + 1;k < w;k++)
		{
			Mat_out[i2 * w + k] = Mat_out[i2 * w + j2EqEnd];     // 右角 赋值
		}
		count=0;
	}
}
























