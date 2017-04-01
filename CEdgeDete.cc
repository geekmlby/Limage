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
	int tmpWidthStep;
	int tmp;
	edgeMat = new uchar[MAXHEIGHT * MAXWIDTH];

	memset(edgeMat,MAXHEIGHT * MAXWIDTH,0);
	tmpWidthStep = (0 == (srcImg -> width) % 4)?(srcImg -> width):(srcImg -> width) + (4 - ((srcImg -> width) % 4));	
	for(int i = 1;i < imgHeight - 1;i++)
	{
		for(int j = 1;j < imgWidth - 1;j++)
		{
			Gx = (-1) * grayMat[(i - 1) * tmpWidthStep + (j - 1)] + grayMat[(i - 1) * tmpWidthStep + (j + 1)] +
					 (-2) * grayMat[i * tmpWidthStep + (j - 1)] + 2 * grayMat[i * tmpWidthStep + (j + 1)] +
					 (-1) * grayMat[(i + 1) * tmpWidthStep + (j - 1)] + grayMat[(i + 1) * tmpWidthStep + (j + 1)];
			Gy = grayMat[(i - 1) * tmpWidthStep + (j - 1)] + 2 * grayMat[(i - 1) * tmpWidthStep + j] + grayMat[(i - 1) * tmpWidthStep + (j + 1)]
					 +
					 (-1) * grayMat[(i + 1) * tmpWidthStep + (j - 1)] + (-2) * grayMat[(i + 1) * tmpWidthStep + j] + 
					 (-1) * grayMat[(i + 1) * tmpWidthStep + (j + 1)];

			tmp = sqrt(Gx * Gx + Gy * Gy);
			if(tmp > 150)
			{
				edgeMat[i * tmpWidthStep + j] = 255;
			}
		}
	}
}

























