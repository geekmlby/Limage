#include"CEdgeDete.h"
#include<stdio.h>
#include<iostream>

CEdgeDete::CEdgeDete()
{
	edgeMat = new uchar[MAXHEIGHT * MAXWIDTH];
}

CEdgeDete::~CEdgeDete()
{
	delete edgeMat;
	edgeMat = NULL;
}

void CEdgeDete::FlipMat(uchar* matrix_out,
							 					uchar* matrix,
							 					int height,
							 					int width,
							 					int eqH,
							 					int eqW)
{
	int i,j;
	uchar* tmpMat;

	tmpMat = new uchar[MAXHEIGHT * MAXWIDTH];

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
	/*WriteTxt<uchar>("/home/wangli/Limage/flippedMat.txt",
									matrix_out,
									height + 2 * eqH,
									width + 2 * eqW);*/

	delete tmpMat;
	tmpMat = NULL;
}

void CEdgeDete::SobelEdgeDete()
{
	int tmp;
	static const int oper_Gx[9] = {-1,-2,-1,0,0,0,1,2,1};
	static const int oper_Gy[9] = {-1,0,1,-2,0,2,-1,0,1};

	uchar* flippedMat;
	int conv_Gx,conv_Gy;

	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];

	FlipMat(flippedMat,
					imgGrayMat,
					imgHeight,
					imgGrayWidthStep,
				  1,
					1);
	for(int i = 1;i < imgHeight + 1;i++)
	{
		for(int j = 1;j < imgGrayWidthStep + 1;j++)
		{
			conv_Gx = (-1) * flippedMat[(i - 1) * (imgGrayWidthStep + 2) + (j - 1)] + flippedMat[(i - 1) * (imgGrayWidthStep + 2) + (j + 1)] +
				 				(-2) * flippedMat[i * (imgGrayWidthStep + 2) + (j - 1)] + 2 * flippedMat[i * (imgGrayWidthStep + 2) + (j + 1)] +
				 				(-1) * flippedMat[(i + 1) * (imgGrayWidthStep + 2) + (j - 1)] + flippedMat[(i + 1) * (imgGrayWidthStep + 2) + (j + 1)];
			conv_Gy = flippedMat[(i - 1) * (imgGrayWidthStep + 2) + (j - 1)] + 2 * flippedMat[(i - 1) * (imgGrayWidthStep + 2) + j] + 
								flippedMat[(i - 1) * (imgGrayWidthStep + 2) + (j + 1)] + (-1) * flippedMat[(i + 1) * (imgGrayWidthStep + 2) + (j - 1)] + 
								(-2) * flippedMat[(i + 1) * (imgGrayWidthStep + 2) + j] + (-1) * flippedMat[(i + 1) * (imgGrayWidthStep + 2) + (j + 1)];

			tmp = sqrt(SQUARE(conv_Gx) + SQUARE(conv_Gy));
			if(tmp > 100)
			{
				edgeMat[(i - 1) * imgGrayWidthStep + (j - 1)] = 255;
			}
		}
	}
	/*WriteTxt<uchar>("/home/wangli/Limage/edgeMat.txt",
									edgeMat,
									imgHeight,
									imgGrayWidthStep);*/
}

void CEdgeDete::LaplaceEdgeDete()
{
	double maxValue,minValue;
	double* tmpArray;
	uchar* flippedMat;

	maxValue = 0;
	minValue = 0;
	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	tmpArray = new double[MAXHEIGHT * MAXWIDTH];

	FlipMat(flippedMat,
					imgGrayMat,
					imgHeight,
					imgGrayWidthStep,
				  1,
					1);
	for(int i = 1;i < imgHeight + 1;i++)
	{
		for(int j = 1;j < imgGrayWidthStep + 1;j++)
		{
			tmpArray[(i - 1) * imgGrayWidthStep + (j - 1)] = flippedMat[(i - 1) * (imgGrayWidthStep + 2) + j] + 
																											 flippedMat[i * (imgGrayWidthStep + 2) + (j - 1)] + 
																											 flippedMat[i * (imgGrayWidthStep + 2) + (j + 1)] + 
																											 flippedMat[(i + 1) * (imgGrayWidthStep + 2) + j] - 
																											 4 * flippedMat[i * (imgGrayWidthStep + 2) + j];

			maxValue = MAXVALUE(tmpArray[(i - 1) * imgGrayWidthStep + (j - 1)],maxValue);
			minValue = MINVALUE(tmpArray[(i - 1) * imgGrayWidthStep + (j - 1)],minValue);
		}
	}
	for(int i = 0;i < imgHeight;i++)
	{
		for(int j = 0;j < imgGrayWidthStep;j++)
		{
			edgeMat[i * imgGrayWidthStep + j] = ((tmpArray[i * imgGrayWidthStep + j] - minValue) / (maxValue - minValue)) * 255;
			if(edgeMat[i * imgGrayWidthStep + j] > 150)
			{
				edgeMat[i * imgGrayWidthStep + j] = 255;
			}
		}
	}
	WriteTxt<uchar>("/home/wangli/Limage/edgeMat.txt",
									edgeMat,
									imgHeight,
									imgGrayWidthStep);
}























