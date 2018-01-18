#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

#include "CDIP.h"

CDIP::CDIP()
{
    pImg_srcImg = NULL;
	puc_imgData = NULL;
	puc_imgRMat = NULL;
	puc_imgGMat = NULL;
	puc_imgBMat = NULL;
	puc_imgGrayMat = NULL;
	edgeMat = new uchar[MAXHEIGHT * MAXWIDTH];
}

CDIP::~CDIP()
{
	delete puc_imgGrayMat;
	delete puc_imgBMat;
	delete puc_imgGMat;
	delete puc_imgRMat;
	puc_imgGrayMat = NULL;
	puc_imgBMat = NULL;
	puc_imgGMat = NULL;
	puc_imgRMat = NULL;
	cvReleaseImage(&pImg_srcImg);
	delete edgeMat;
	edgeMat = NULL;
}

void CDIP::ReadImage(char* path)
{	
	pImg_srcImg = cvLoadImage(path,-1);
	imgH = pImg_srcImg -> height;
	imgW = pImg_srcImg -> width;
	imgChannels = pImg_srcImg -> nChannels;
	imgDepth = pImg_srcImg -> depth;
	imgSize = pImg_srcImg -> imageSize;
	imgWidthStep = pImg_srcImg -> widthStep;
	puc_imgData = (uchar*)pImg_srcImg -> imageData;
	cout << "***************** The Data of image,as shown below: *****************" << endl;
	cout << "The h of the image is:" << imgH << endl;
	cout << "The w of the image is:" << imgW << endl;
	cout << "The channels of the image is:" << imgChannels << endl;
	cout << "The depth of the image is: " << imgDepth << endl;
	cout << "The imageSize of the image is: " << imgSize << endl;
	cout << "The widthStep of the image is:" << imgWidthStep << endl;
	cout << "*********************************************************************" << endl;
}

void CDIP::ShowImage()
{
	if(0 != pImg_srcImg)
	{
		cvNamedWindow("srcImage",0);
		cvShowImage("srcImage",pImg_srcImg);
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
					 uchar* Mat,
					 int h,
					 int w,
					 int depth,
					 int channels)
{
	IplImage* pImg_tmp = NULL;
	pImg_tmp = cvCreateImage(cvSize(w,h),depth,channels);
	pImg_tmp -> imageData = (char*)Mat;
	/*cout << "+++++++++++++++++ The Data of tmpImg,as shown below: ++++++++++++++++" << endl;
	cout << "The h of the tmpImg is:" << pImg_tmp -> h << endl;
	cout << "The w of the tmpImg is:" << pImg_tmp -> w << endl;
	cout << "The channels of the tmpImg is:" << pImg_tmp -> nChannels<< endl;
	cout << "The depth of the tmpImg is: " << pImg_tmp -> depth << endl;
	cout << "The imageSize of the tmpImg is: " << pImg_tmp -> imageSize << endl;
	cout << "The widthStep of the tmpImg is:" << pImg_tmp -> widthStep << endl;
	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;*/
	cvNamedWindow(windowName,0);
	cvShowImage(windowName,pImg_tmp);
	cvWaitKey(0);
	cvDestroyWindow(windowName);
	cvReleaseImage(&pImg_tmp);
}

void CDIP::GetImageRGB()
{
	puc_imgRMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	puc_imgGMat = new uchar[MAXHEIGHT * MAXWIDTH];
	puc_imgBMat = new uchar[MAXHEIGHT * MAXWIDTH];
	for(int i = 0;i < imgH;i++)
	{
		for(int j = 0;j < imgW;j++)
		{
			puc_imgBMat[i * imgW + j] = puc_imgData[i * imgWidthStep + j * imgChannels + 0];
			puc_imgGMat[i * imgW + j] = puc_imgData[i * imgWidthStep + j * imgChannels + 1];
			puc_imgRMat[i * imgW + j] = puc_imgData[i * imgWidthStep + j * imgChannels + 2];
		}
	}
}

void CDIP::GetGrayImage()
{	
	double grayValueSum;
	int pos;
	puc_imgGrayMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(3 == imgChannels)
	{
		if(NULL == puc_imgRMat || NULL == puc_imgGMat || NULL == puc_imgBMat)
		{
			GetImageRGB();
		}
		else
		{
			for(int i = 0;i < imgH;i++)
			{
				for(int j = 0;j < imgW;j++)
				{
					grayValueSum = 2989 * puc_imgRMat[i * imgW + j] +
								   5866 * puc_imgGMat[i * imgW + j] +
								   1145 * puc_imgBMat[i * imgW + j];
					puc_imgGrayMat[i * imgW + j] = (int)(grayValueSum / 10000);
 				}
			}
		}
	}
	if(1 == imgChannels)
	{
		for(int i = 0;i < imgH;i++)
		{
			for(int j = 0;j < imgW;j++)
			{
				puc_imgGrayMat[i * imgW + j] = puc_imgData[i * imgWidthStep + j];
			}
		}
	}	
	ShowImage("GrayImg",
			  puc_imgGrayMat,
			  imgH,
              imgW);
	WriteTxt<uchar>("/home/wangli/Limage/puc_imgGrayMat.txt",
					puc_imgGrayMat,
					imgH,
					imgW);
}

void CDIP::FlipMat(uchar* Mat_out,
				   uchar* Mat,
				   int h,
				   int w,
				   int filterH,
				   int filterW)
{
	int i,j;
	int eqH,eqW;
	uchar* puc_tmpMat;

	eqH = filterH / 2;
	eqW = filterW / 2;
	puc_tmpMat = new uchar[MAXHEIGHT * MAXWIDTH];

	if(h <= 0 || w <= 0 || eqH > h || eqW > w)
	{
		cout << "The input parameters error!" << endl;
		return;
	}
	//Flip vertical
	for(i = 0;i < eqH;i++)
	{
		memcpy(puc_tmpMat + i * w,Mat + (eqH - (i + 1)) * w,w);
	}
	memcpy(puc_tmpMat + eqH * w,Mat,h * w);
	for(i = h + eqH;i < h + 2 * eqH;i++)
	{
		memcpy(puc_tmpMat + i * w,Mat + (h - (i - h - eqH + 1)) * w,w);
	}
	//Flip horizontal
	for(i = 0;i < h + 2 * eqH;i++)
	{								
		for(j = 0;j < (w + 2 * eqW);j++)
		{
			if(j < eqW)
			{
			    Mat_out[i * (w + 2 * eqW) + j] = puc_tmpMat[i * w + (eqW - (j + 1))];
			}
			else if(j >= w + eqW)
			{
				Mat_out[i * (w + 2 * eqW) + j] = puc_tmpMat[i * w + (w - (j - w - eqW + 1))];
			}
			else
			{
				Mat_out[i * (w + 2 * eqW) + j] = puc_tmpMat[i * w + (j - eqW)];
			}
		}
	}

	/*ShowImage("FlipMatImg",
				Mat_out,
				(h + 2 * eqH),
				(w + 2 * eqW));*/

	delete puc_tmpMat;
	puc_tmpMat = NULL;
}

void CDIP::EdgeDete_Sobel(uchar* Mat_out,
						 uchar* Mat,
						 int h,
						 int w,
						 int thre)
{
	int tmp;
	uchar* puc_flippedMat;
	int conv_Gx,conv_Gy;

	puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];

	memset(Mat_out,0,MAXHEIGHT * MAXWIDTH);

	FlipMat(puc_flippedMat,
			Mat,
			h,
			w,
			3,
			3);
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat_SobelEdgeDete.txt",
					puc_flippedMat,
					h + 2,
					w + 2);

	for(int i = 1;i < h + 1;i++)
	{
		for(int j = 1;j < w + 1;j++)
		{
			conv_Gx = (-1) * puc_flippedMat[(i - 1) * (w + 2) + (j - 1)] + puc_flippedMat[(i - 1) * (w + 2) + (j + 1)] +
				 	  (-2) * puc_flippedMat[i * (w + 2) + (j - 1)] + 2 * puc_flippedMat[i * (w + 2) + (j + 1)] +
				 	  (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j - 1)] + puc_flippedMat[(i + 1) * (w + 2) + (j + 1)];
			conv_Gy = puc_flippedMat[(i - 1) * (w + 2) + (j - 1)] + 2 * puc_flippedMat[(i - 1) * (w + 2) + j] + 
					  puc_flippedMat[(i - 1) * (w + 2) + (j + 1)] + (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j - 1)] + 
					  (-2) * puc_flippedMat[(i + 1) * (w + 2) + j] + (-1) * puc_flippedMat[(i + 1) * (w + 2) + (j + 1)];

			tmp = sqrt(SQUARE(conv_Gx) + SQUARE(conv_Gy));
			if(tmp > thre)
			{
				Mat_out[(i - 1) * w + (j - 1)] = 255;
			}
		}
	}

	ShowImage("SobelEdgeDeteImg",
			  Mat_out,
			  h,
			  w);
	WriteTxt<uchar>("/home/wangli/Limage/SobelEdgeDete.txt",
					edgeMat,
					h,
					w);

	delete puc_flippedMat;
	puc_flippedMat = NULL;
}

void CDIP::EdgeDete_Laplace(uchar* Mat_out,
						   uchar* Mat,
						   int h,
						   int w,
						   int thresold)
{
	double maxValue,minValue;
	double* tmpArray;
	uchar* puc_flippedMat;

	maxValue = 0;
	minValue = 0;
	puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	tmpArray = new double[MAXHEIGHT * MAXWIDTH];

	memset(Mat_out,0,MAXHEIGHT * MAXWIDTH);

	FlipMat(puc_flippedMat,
			Mat,
			h,
			w,
			3,
			3);
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat_LaplaceEdgeDete.txt",
					puc_flippedMat,
					h + 2,
					w + 2);

	for(int i = 1;i < h + 1;i++)
	{
		for(int j = 1;j < w + 1;j++)
		{
			tmpArray[(i - 1) * w + (j - 1)] = puc_flippedMat[(i - 1) * (w + 2) + j] + puc_flippedMat[i * (w + 2) + (j - 1)] + 
												  puc_flippedMat[i * (w + 2) + (j + 1)] + puc_flippedMat[(i + 1) * (w + 2) + j] - 
												  4 * puc_flippedMat[i * (w + 2) + j];

			maxValue = MAXV(tmpArray[(i - 1) * w + (j - 1)],maxValue);
			minValue = MINV(tmpArray[(i - 1) * w + (j - 1)],minValue);
		}
	}
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			edgeMat[i * w + j] = ((tmpArray[i * w + j] - minValue) / (maxValue - minValue)) * 255;
			if(edgeMat[i * w + j] > thresold)
			{
				edgeMat[i * w + j] = 255;
			}
			else
			{
				edgeMat[i * w + j] = 0;
			}
		}
	}

	ShowImage("LaplaceEdgeDeteImg",
			  Mat_out,
			  h,
			  w);
	WriteTxt<uchar>("/home/wangli/Limage/LaplaceEdgeDete.txt",
					edgeMat,
					h,
					w);

	delete puc_flippedMat;
	delete tmpArray;
	puc_flippedMat = NULL;
	tmpArray = NULL;
}

void CDIP::GaussianBlur(uchar* Mat_out,
						uchar* Mat,
						int h,
						int w,
						int filterH,
						int filterW,
						double sigma)
{
	uchar* puc_flippedMat;
	double* windowArray;

	puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	windowArray = new double[MAXLENGTH];

	FlipMat(puc_flippedMat,
			Mat,
			h,
			w,
			filterH,
			filterW);
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat_GaussianBlur.txt",
					puc_flippedMat,
					h + filterH - 1,
					w + filterW - 1);
	Calconv(Mat_out,
			puc_flippedMat,
			h,
			w,
			filterH,
			filterW,
			sigma);

	ShowImage("GaussianBlurImg",
			  Mat_out,
			  h,
			  w);
	WriteTxt<uchar>("/home/wangli/Limage/GaussianBlur.txt",
					Mat_out,
					h,
					w);

	delete puc_flippedMat;
	delete windowArray;
	puc_flippedMat = NULL;
	windowArray = NULL;
}

void CDIP::Calconv(uchar* Mat_out,
				   uchar* Mat,
				   int h,
				   int w,
				   int filterH,
				   int filterW,
				   double sigma)
{
	double tmp;
	int eqH,eqW;
	double sum;
	double* weightArray;
	double* windowArray;

	tmp = 0;
	eqH = filterH / 2;
	eqW = filterW / 2;
	windowArray = new double[MAXLENGTH];
	weightArray = new double[MAXLENGTH];

	for(int x = (-1 * eqH);x < (eqH + 1);x++)
	{
		for(int y = (-1 * eqW);y < (eqW + 1);y++)
		{
			weightArray[(x + eqH) * filterW + (y + eqW)] = 
            exp(-1 * (SQUARE(x) + SQUARE(y)) / (2 * SQUARE(sigma))) / (2 * PI * SQUARE(sigma));
			sum = sum + weightArray[(x + eqH) * filterW + (y + eqW)];
		}
	}
	for(int i = 0;i < (filterH * filterW);i++)
	{
		weightArray[i] = weightArray[i] / sum;
	}
	for(int i = eqH;i < h + eqH;i++)
	{
		for(int j = eqW;j < w + eqW;j++)
		{
			for(int x = (-1 * eqH);x < (eqH + 1);x++)
			{
				for(int y = (-1 * eqW);y < (eqW + 1);y++)
				{
					windowArray[(x + eqH) * filterW + (y + eqW)] = Mat[(i + x) * (w + 2 * eqW) + (j + y)];
				}
			}	
			for(int k = 0;k < (filterH * filterW);k++)
			{
				tmp += (windowArray[k] * weightArray[k]);
				windowArray[k] = 0;
			}	
			Mat_out[(i - eqH) * w + (j - eqW)] = (uchar)tmp;
			tmp = 0;
		}
	}

	delete weightArray;
	delete windowArray;
	windowArray = NULL;
	weightArray = NULL;
}

void CDIP::EdgeDete_Canny(uchar* Mat_out,
						  uchar* Mat,
						  int h,
						  int w,
						  int filterH,
						  int filterW,
						  int upThresold,
						  int downThresold,
						  double sigma)
{
	int tmp;
	uchar* gaussianMat;
	uchar* puc_flippedMat;
	uchar* flippedMat2;
	uchar* tmpArray;
	uchar* Gx;
	uchar* Gy;
	double* Gxy;
	double* Axy;
	double alpha;
	double scale;
	double tmp1,tmp2;

	gaussianMat = new uchar[MAXHEIGHT * MAXWIDTH];
	puc_flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	flippedMat2 = new uchar[MAXHEIGHT * MAXWIDTH];
	tmpArray = new uchar[3 * 3];
	Gx = new uchar[MAXHEIGHT * MAXWIDTH];
	Gy = new uchar[MAXHEIGHT * MAXWIDTH];
	Gxy = new double[MAXHEIGHT * MAXWIDTH];
	Axy = new double[MAXHEIGHT * MAXWIDTH];

	memset(Mat_out,0,MAXHEIGHT * MAXWIDTH);

	if(upThresold < downThresold)
	{
		tmp = upThresold;
		upThresold = downThresold;
		downThresold = tmp; 
	}

	memset(gaussianMat,0,MAXHEIGHT * MAXWIDTH);

	GaussianBlur(gaussianMat,
				 Mat,
				 h,
				 w,
				 filterH,
				 filterW,
				 sigma);

	//Calculate the image gradient,moreovre,calculate the edge amplitude and angle according to the gradient.
	FlipMat(puc_flippedMat,
		    gaussianMat,
			h,
			w,
			3,
			3);
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			Gx[i * w + j] = (puc_flippedMat[i * (w + 2) + (j + 2)] - puc_flippedMat[i * (w + 2) + j]) / 2;
			Gy[i * w + j] = (puc_flippedMat[(i + 2) * (w + 2) + j] - puc_flippedMat[i * (w + 2) + j]) / 2;
			Gxy[i * w + j] = sqrt(SQUARE(Gx[i * w + j]) + SQUARE(Gy[i * w + j]));
			Axy[i * w + j] = (atan2(Gy[i * w + j],Gx[i * w + j]) / PI) * 180;
			if(Axy[i * w + j] < 0)
			{
				Axy[i * w + j] = Axy[i * w + j] + 180;
				alpha = (Axy[i * w + j] / 180);
			}
			if(alpha < 45)
			{
				scale = tan(alpha);
				tmp1 = (double)(((double)(puc_flippedMat[i * (w + 2) + j + 2] - puc_flippedMat[(i + 1) * (w + 2) + j + 2])) * scale +
					   puc_flippedMat[(i + 1) * (w + 2) + j + 2]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j] - puc_flippedMat[(i + 1) * (w + 2) + j])) * scale +
					   puc_flippedMat[(i + 1) * (w + 2) + j]);
				if(tmp1 > gaussianMat[i * w + j] || tmp2 > gaussianMat[i * w + j])
				{
					gaussianMat[i * w + j] = 0;
				}
			}
			else if(alpha >= 45 && alpha < 90)
			{
				scale = tan(alpha);
				tmp1 = (double)(((double)(puc_flippedMat[i * (w + 2) + j + 2] - puc_flippedMat[i * (w + 2) + j + 1])) * scale +
					   puc_flippedMat[i * (w + 2) + j + 1]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j + 1] - puc_flippedMat[(i + 2) * (w + 2) + j])) * scale +
					   puc_flippedMat[(i + 2) * (w + 2) + j]);
				if(tmp1 > gaussianMat[i * w + j] || tmp2 > gaussianMat[i * w + j])
				{
					gaussianMat[i * w + j] = 0;
				}
			}
			else if(alpha >= 90)
			{
				scale = tan((alpha - 90));
				tmp1 = (double)(((double)(puc_flippedMat[i * (w + 2) + j + 1] - puc_flippedMat[i * (w + 2) + j])) * scale +
					   puc_flippedMat[i * (w + 2) + j]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j + 2] - puc_flippedMat[(i + 2) * (w + 2) + j + 1])) * scale 
                       + puc_flippedMat[(i + 2) * (w + 2) + j + 1]);
				if(tmp1 > gaussianMat[i * w + j] || tmp2 > gaussianMat[i * w + j])
				{
					gaussianMat[i * w + j] = 0;
				}
			}
			else
			{
				scale = tan((180 - alpha));
				tmp1 = (double)(((double)(puc_flippedMat[(i + 1) * (w + 2) + j] - puc_flippedMat[i * (w + 2) + j])) * scale +
							 puc_flippedMat[i * (w + 2) + j]);
				tmp2 = (double)(((double)(puc_flippedMat[(i + 2) * (w + 2) + j + 2] - puc_flippedMat[(i + 1) * (w + 2) + j + 2])) * scale                        + puc_flippedMat[(i + 1) * (w + 2) + j + 2]);
				if(tmp1 > gaussianMat[i * w + j] || tmp2 > gaussianMat[i * w + j])
				{
					gaussianMat[i * w + j] = 0;
				}
			}
		}
	}
	ShowImage("NMSImg",
			  gaussianMat,
			  h,
			  w);
	FlipMat(flippedMat2,
			gaussianMat,
			h,
			w,
			3,
			3);
	for(int i = 0;i < h;i++)
	{
		for(int j = 0;j < w;j++)
		{
			if(gaussianMat[i * w + j] >= upThresold)
			{
				Mat_out[i * w + j] = 255;
			}
			else if(gaussianMat[i * w + j] < upThresold && gaussianMat[i * w + j] >= downThresold)
			{
				for(int w = i;w < i + 2;w++)
				{
					for(int l = j;l < j + 2;l++)
					{
						for(int k = 0;k < 3 * 3;k++)
						{
							tmpArray[k] = flippedMat2[w * (w + 2) + l];
						}
					}
				}
				for(int k = 0;k < 3 * 3;k++)
				{
					if(tmpArray[k] >= upThresold)
					{
						Mat_out[i * w + j] = 255;
					}
				}
			}
			else
			{
				Mat_out[i * w + j] = 0;
			}
		}
	}
	ShowImage("CannyEdgeDeteImg",
			  Mat_out,
			  h,
			  w);
	WriteTxt<uchar>("/home/wangli/Limage/CannyEdgeDete.txt",
					Mat_out,
					h,
					w);

	delete gaussianMat;
	delete puc_flippedMat;
	delete flippedMat2;
	delete tmpArray;
	delete Gx;
	delete Gy;
	delete Gxy;
	delete Axy;
	gaussianMat = NULL;
	puc_flippedMat = NULL;
	flippedMat2 = NULL;
	Gx = NULL;
	Gy = NULL;
	Gxy = NULL;
	Axy = NULL;
	tmpArray = NULL;
}












