#include"CEdgeDete.h"
#include<stdio.h>
#include<iostream>
#include<math.h>

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
										 					int thresold,
															int filterH,
															int filterW)
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
				  filterH,
					filterW);
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
	/*WriteTxt<uchar>("/home/wangli/Limage/edgeMat.txt",
									edgeMat,
									imgHeight,
									imgWidthStep);*/
	delete flippedMat;
	flippedMat = NULL;
}

void CEdgeDete::LaplaceEdgeDete(uchar* matrix_out,
										 						uchar* matrix,
										 						int height,
										 						int width,
										 						int thresold,
																int filterH,
																int filterW)
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
				  filterH,
					filterW);
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
	WriteTxt<uchar>("/home/wangli/Limage/edgeMat.txt",
									edgeMat,
									imgHeight,
									imgWidthStep);
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
	double* weightArray;
	double* windowArray;

	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	weightArray = new double[MAXLENGTH];
	windowArray = new double[MAXLENGTH];

	FlipMat(flippedMat,
					matrix,
					height,
					width,
				  filterH,
					filterW);
	CalConv(matrix_out,
					flippedMat,
					//weightArray,
					height,
					width,
					filterH,
					filterW,
					sigma);
	ShowImage("GaussianBlurImage",
						matrix_out,
						height,
						width);
	WriteTxt<uchar>("/home/wangli/Limage/gaussianBlurMat.txt",
									matrix_out,
									height,
									width);

	delete flippedMat;
	delete weightArray;
	delete windowArray;
	flippedMat = NULL;
	weightArray = NULL;
	windowArray = NULL;
}

void CEdgeDete::CalConv(uchar* matrix_out,
						   					uchar* matrix,
							 					//double* weightMatrix,
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
	gaussianMat = new uchar[MAXHEIGHT * MAXWIDTH];

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

	delete gaussianMat;
	gaussianMat = NULL;
}



















