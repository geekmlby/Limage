#include "CEdgeDete.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

CEdgeDete::CEdgeDete()
{
	edgeMat = new uchar[MAXHEIGHT * MAXWIDTH];
}

CEdgeDete::~CEdgeDete()
{
	delete edgeMat;
	edgeMat = NULL;
}

void CEdgeDete::SobelEdgeDete(uchar* matrix_out,
										 					uchar* matrix,
										 					int height,
										 					int width,
										 					int thresold)
{
	int tmp;
	uchar* flippedMat;
	int conv_Gx,conv_Gy;

	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];

	memset(matrix_out,0,MAXHEIGHT * MAXWIDTH);

	FlipMat(flippedMat,
					matrix,
					height,
					width,
				  3,
					3);
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat_SobelEdgeDete.txt",
									flippedMat,
									height + 2,
									width + 2);

	for(int i = 1;i < height + 1;i++)
	{
		for(int j = 1;j < width + 1;j++)
		{
			conv_Gx = (-1) * flippedMat[(i - 1) * (width + 2) + (j - 1)] + flippedMat[(i - 1) * (width + 2) + (j + 1)] +
				 				(-2) * flippedMat[i * (width + 2) + (j - 1)] + 2 * flippedMat[i * (width + 2) + (j + 1)] +
				 				(-1) * flippedMat[(i + 1) * (width + 2) + (j - 1)] + flippedMat[(i + 1) * (width + 2) + (j + 1)];
			conv_Gy = flippedMat[(i - 1) * (width + 2) + (j - 1)] + 2 * flippedMat[(i - 1) * (width + 2) + j] + 
								flippedMat[(i - 1) * (width + 2) + (j + 1)] + (-1) * flippedMat[(i + 1) * (width + 2) + (j - 1)] + 
								(-2) * flippedMat[(i + 1) * (width + 2) + j] + (-1) * flippedMat[(i + 1) * (width + 2) + (j + 1)];

			tmp = sqrt(SQUARE(conv_Gx) + SQUARE(conv_Gy));
			if(tmp > thresold)
			{
				matrix_out[(i - 1) * width + (j - 1)] = 255;
			}
		}
	}

	ShowImage("SobelEdgeDeteImg",
						matrix_out,
						height,
						width);
	WriteTxt<uchar>("/home/wangli/Limage/SobelEdgeDete.txt",
									edgeMat,
									height,
									width);

	delete flippedMat;
	flippedMat = NULL;
}

void CEdgeDete::LaplaceEdgeDete(uchar* matrix_out,
										 						uchar* matrix,
										 						int height,
										 						int width,
										 						int thresold)
{
	double maxValue,minValue;
	double* tmpArray;
	uchar* flippedMat;

	maxValue = 0;
	minValue = 0;
	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	tmpArray = new double[MAXHEIGHT * MAXWIDTH];

	memset(matrix_out,0,MAXHEIGHT * MAXWIDTH);

	FlipMat(flippedMat,
					matrix,
					height,
					width,
				  3,
					3);
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat_LaplaceEdgeDete.txt",
									flippedMat,
									height + 2,
									width + 2);

	for(int i = 1;i < height + 1;i++)
	{
		for(int j = 1;j < width + 1;j++)
		{
			tmpArray[(i - 1) * width + (j - 1)] = flippedMat[(i - 1) * (width + 2) + j] + flippedMat[i * (width + 2) + (j - 1)] + 
																						flippedMat[i * (width + 2) + (j + 1)] + flippedMat[(i + 1) * (width + 2) + j] - 
																						4 * flippedMat[i * (width + 2) + j];

			maxValue = MAXVALUE(tmpArray[(i - 1) * width + (j - 1)],maxValue);
			minValue = MINVALUE(tmpArray[(i - 1) * width + (j - 1)],minValue);
		}
	}
	for(int i = 0;i < height;i++)
	{
		for(int j = 0;j < width;j++)
		{
			edgeMat[i * width + j] = ((tmpArray[i * width + j] - minValue) / (maxValue - minValue)) * 255;
			if(edgeMat[i * width + j] > thresold)
			{
				edgeMat[i * width + j] = 255;
			}
			else
			{
				edgeMat[i * width + j] = 0;
			}
		}
	}

	ShowImage("LaplaceEdgeDeteImg",
						matrix_out,
						height,
						width);
	WriteTxt<uchar>("/home/wangli/Limage/LaplaceEdgeDete.txt",
									edgeMat,
									height,
									width);

	delete flippedMat;
	delete tmpArray;
	flippedMat = NULL;
	tmpArray = NULL;
}

void CEdgeDete::GaussianBlur(uchar* matrix_out,
														 uchar* matrix,
														 int height,
														 int width,
														 int filterH,
														 int filterW,
														 double sigma)
{
	uchar* flippedMat;
	double* windowArray;

	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	windowArray = new double[MAXLENGTH];

	FlipMat(flippedMat,
					matrix,
					height,
					width,
				  filterH,
					filterW);
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat_GaussianBlur.txt",
									flippedMat,
									height + filterH - 1,
									width + filterW - 1);
	CalConv(matrix_out,
					flippedMat,
					height,
					width,
					filterH,
					filterW,
					sigma);

	ShowImage("GaussianBlurImg",
						matrix_out,
						height,
						width);
	WriteTxt<uchar>("/home/wangli/Limage/GaussianBlur.txt",
									matrix_out,
									height,
									width);

	delete flippedMat;
	delete windowArray;
	flippedMat = NULL;
	windowArray = NULL;
}

void CEdgeDete::CalConv(uchar* matrix_out,
						   					uchar* matrix,
							 					int height,
							 					int width,
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
			weightArray[(x + eqH) * filterW + (y + eqW)] = exp(-1 * (SQUARE(x) + SQUARE(y)) / (2 * SQUARE(sigma))) / (2 * PI * SQUARE(sigma));
			sum = sum + weightArray[(x + eqH) * filterW + (y + eqW)];
		}
	}
	for(int i = 0;i < (filterH * filterW);i++)
	{
		weightArray[i] = weightArray[i] / sum;
	}
	for(int i = eqH;i < height + eqH;i++)
	{
		for(int j = eqW;j < width + eqW;j++)
		{
			for(int x = (-1 * eqH);x < (eqH + 1);x++)
			{
				for(int y = (-1 * eqW);y < (eqW + 1);y++)
				{
					windowArray[(x + eqH) * filterW + (y + eqW)] = matrix[(i + x) * (width + 2 * eqW) + (j + y)];
				}
			}	
			for(int k = 0;k < (filterH * filterW);k++)
			{
				tmp += (windowArray[k] * weightArray[k]);
				windowArray[k] = 0;
			}	
			matrix_out[(i - eqH) * width + (j - eqW)] = (uchar)tmp;
			tmp = 0;
		}
	}

	delete weightArray;
	delete windowArray;
	windowArray = NULL;
	weightArray = NULL;
}

void CEdgeDete::CannyEdgeDete(uchar* matrix_out,
										 					uchar* matrix,
										 					int height,
										 					int width,
															int filterH,
															int filterW,
										 					int upThresold,
													 		int downThresold,
															double sigma)
{
	int tmp;
	uchar* gaussianMat;
	uchar* flippedMat;
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
	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	flippedMat2 = new uchar[MAXHEIGHT * MAXWIDTH];
	tmpArray = new uchar[3 * 3];
	Gx = new uchar[MAXHEIGHT * MAXWIDTH];
	Gy = new uchar[MAXHEIGHT * MAXWIDTH];
	Gxy = new double[MAXHEIGHT * MAXWIDTH];
	Axy = new double[MAXHEIGHT * MAXWIDTH];

	memset(matrix_out,0,MAXHEIGHT * MAXWIDTH);

	if(upThresold < downThresold)
	{
		tmp = upThresold;
		upThresold = downThresold;
		downThresold = tmp; 
	}

	memset(gaussianMat,0,MAXHEIGHT * MAXWIDTH);

	GaussianBlur(gaussianMat,
							 matrix,
							 height,
							 width,
							 filterH,
							 filterW,
							 sigma);

	//Calculate the image gradient,moreovre,calculate the edge amplitude and angle according to the gradient.
	FlipMat(flippedMat,
				  gaussianMat,
					height,
					width,
					3,
					3);
	for(int i = 0;i < height;i++)
	{
		for(int j = 0;j < width;j++)
		{
			Gx[i * width + j] = (flippedMat[i * (width + 2) + (j + 2)] - flippedMat[i * (width + 2) + j]) / 2;
			Gy[i * width + j] = (flippedMat[(i + 2) * (width + 2) + j] - flippedMat[i * (width + 2) + j]) / 2;
			Gxy[i * width + j] = sqrt(SQUARE(Gx[i * width + j]) + SQUARE(Gy[i * width + j]));
			Axy[i * width + j] = (atan2(Gy[i * width + j],Gx[i * width + j]) / PI) * 180;
			if(Axy[i * width + j] < 0)
			{
				Axy[i * width + j] = Axy[i * width + j] + 180;
				alpha = (Axy[i * width + j] / 180);
			}
			if(alpha < 45)
			{
				scale = tan(alpha);
				tmp1 = (double)(((double)(flippedMat[i * (width + 2) + j + 2] - flippedMat[(i + 1) * (width + 2) + j + 2])) * scale +
							 flippedMat[(i + 1) * (width + 2) + j + 2]);
				tmp2 = (double)(((double)(flippedMat[(i + 2) * (width + 2) + j] - flippedMat[(i + 1) * (width + 2) + j])) * scale +
							 flippedMat[(i + 1) * (width + 2) + j]);
				if(tmp1 > gaussianMat[i * width + j] || tmp2 > gaussianMat[i * width + j])
				{
					gaussianMat[i * width + j] = 0;
				}
			}
			else if(alpha >= 45 && alpha < 90)
			{
				scale = tan(alpha);
				tmp1 = (double)(((double)(flippedMat[i * (width + 2) + j + 2] - flippedMat[i * (width + 2) + j + 1])) * scale +
							 flippedMat[i * (width + 2) + j + 1]);
				tmp2 = (double)(((double)(flippedMat[(i + 2) * (width + 2) + j + 1] - flippedMat[(i + 2) * (width + 2) + j])) * scale +
							 flippedMat[(i + 2) * (width + 2) + j]);
				if(tmp1 > gaussianMat[i * width + j] || tmp2 > gaussianMat[i * width + j])
				{
					gaussianMat[i * width + j] = 0;
				}
			}
			else if(alpha >= 90)
			{
				scale = tan((alpha - 90));
				tmp1 = (double)(((double)(flippedMat[i * (width + 2) + j + 1] - flippedMat[i * (width + 2) + j])) * scale +
							 flippedMat[i * (width + 2) + j]);
				tmp2 = (double)(((double)(flippedMat[(i + 2) * (width + 2) + j + 2] - flippedMat[(i + 2) * (width + 2) + j + 1])) * scale +
							 flippedMat[(i + 2) * (width + 2) + j + 1]);
				if(tmp1 > gaussianMat[i * width + j] || tmp2 > gaussianMat[i * width + j])
				{
					gaussianMat[i * width + j] = 0;
				}
			}
			else
			{
				scale = tan((180 - alpha));
				tmp1 = (double)(((double)(flippedMat[(i + 1) * (width + 2) + j] - flippedMat[i * (width + 2) + j])) * scale +
							 flippedMat[i * (width + 2) + j]);
				tmp2 = (double)(((double)(flippedMat[(i + 2) * (width + 2) + j + 2] - flippedMat[(i + 1) * (width + 2) + j + 2])) * scale +
							 flippedMat[(i + 1) * (width + 2) + j + 2]);
				if(tmp1 > gaussianMat[i * width + j] || tmp2 > gaussianMat[i * width + j])
				{
					gaussianMat[i * width + j] = 0;
				}
			}
		}
	}
	ShowImage("NMSImg",
						gaussianMat,
						height,
						width);
	FlipMat(flippedMat2,
				  gaussianMat,
					height,
					width,
					3,
					3);
	for(int i = 0;i < height;i++)
	{
		for(int j = 0;j < width;j++)
		{
			if(gaussianMat[i * width + j] >= upThresold)
			{
				matrix_out[i * width + j] = 255;
			}
			else if(gaussianMat[i * width + j] < upThresold && gaussianMat[i * width + j] >= downThresold)
			{
				for(int w = i;w < i + 2;w++)
				{
					for(int l = j;l < j + 2;l++)
					{
						for(int k = 0;k < 3 * 3;k++)
						{
							tmpArray[k] = flippedMat2[w * (width + 2) + l];
						}
					}
				}
				for(int k = 0;k < 3 * 3;k++)
				{
					if(tmpArray[k] >= upThresold)
					{
						matrix_out[i * width + j] = 255;
					}
				}
			}
			else
			{
				matrix_out[i * width + j] = 0;
			}
		}
	}
	ShowImage("CannyEdgeDeteImg",
						matrix_out,
						height,
						width);
	WriteTxt<uchar>("/home/wangli/Limage/CannyEdgeDete.txt",
									matrix_out,
									height,
									width);

	delete gaussianMat;
	delete flippedMat;
	delete flippedMat2;
	delete tmpArray;
	delete Gx;
	delete Gy;
	delete Gxy;
	delete Axy;
	gaussianMat = NULL;
	flippedMat = NULL;
	flippedMat2 = NULL;
	Gx = NULL;
	Gy = NULL;
	Gxy = NULL;
	Axy = NULL;
	tmpArray = NULL;
}



















