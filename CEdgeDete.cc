#include"CEdgeDete.h"
#include<stdio.h>
#include<iostream>

CEdgeDete::CEdgeDete()
{
}

CEdgeDete::~CEdgeDete()
{
}

void CEdgeDete::Sobel()
{
	int tmp;
	edgeMat = new uchar[MAXHEIGHT * MAXWIDTH];

	memset(edgeMat,MAXHEIGHT * MAXWIDTH,0);
	for(int i = 1;i < imgHeight - 1;i++)
	{
		for(int j = 1;j < imgWidth - 1;j++)
		{
			Gx = (-1) * imgGrayMat[(i - 1) * imgGrayWidthStep + (j - 1)] + imgGrayMat[(i - 1) * imgGrayWidthStep + (j + 1)] +
					 (-2) * imgGrayMat[i * imgGrayWidthStep + (j - 1)] + 2 * imgGrayMat[i * imgGrayWidthStep + (j + 1)] +
					 (-1) * imgGrayMat[(i + 1) * imgGrayWidthStep + (j - 1)] + imgGrayMat[(i + 1) * imgGrayWidthStep + (j + 1)];
			Gy = imgGrayMat[(i - 1) * imgGrayWidthStep + (j - 1)] + 2 * imgGrayMat[(i - 1) * imgGrayWidthStep + j] + 
					 imgGrayMat[(i - 1) * imgGrayWidthStep + (j + 1)] + (-1) * imgGrayMat[(i + 1) * imgGrayWidthStep + (j - 1)] + 
					 (-2) * imgGrayMat[(i + 1) * imgGrayWidthStep + j] + (-1) * imgGrayMat[(i + 1) * imgGrayWidthStep + (j + 1)];

			tmp = sqrt(Gx * Gx + Gy * Gy);
			if(tmp > 100)
			{
				edgeMat[i * imgGrayWidthStep + j] = 255;
			}
		}
	}
}

























