#include"CEdgeDete.h"
#include<stdio.h>
#include<iostream>

CEdgeDete::CEdgeDete()
{
	edgeMat = NULL;
	flipMat_UpDown = NULL;
	flipMat_LeftRight = NULL;
}

CEdgeDete::~CEdgeDete()
{
	delete edgeMat;
	delete flipMat_UpDown;
	delete flipMat_LeftRight;
	edgeMat = NULL;
	flipMat_UpDown = NULL;
	flipMat_LeftRight = NULL;
}

void CEdgeDete::FlipMat(uchar* matrix,
							 					int eqH,
							 					int eqW)
{
	int i,j;
	flipMat_UpDown = new uchar[MAXHEIGHT * MAXWIDTH];
	flipMat_LeftRight = new uchar[MAXHEIGHT * MAXWIDTH];

	for(i = 0;i < eqH;i++)
	{
		memcpy(flipMat_UpDown + i * imgGrayWidthStep,matrix + (eqH - (i + 1)) * imgGrayWidthStep,imgGrayWidthStep);
	}
	memcpy(flipMat_UpDown + eqH * imgGrayWidthStep,matrix,imgHeight * imgGrayWidthStep);
	for(i = imgHeight + eqH;i < imgHeight + 2 * eqH;i++)
	{
		memcpy(flipMat_UpDown + i * imgGrayWidthStep,matrix + (imgHeight - (i - imgHeight - eqH + 1)) * imgGrayWidthStep,imgGrayWidthStep);
	}
	WriteTxt<uchar>("/home/wangli/Limage/flipMat_UpDown.txt",
									flipMat_UpDown,
									imgHeight + 2 * eqH,
									imgGrayWidthStep);		
	for(i = 0;i < imgHeight + 2 * eqH;i++)
	{								
		for(j = 0;j < (imgGrayWidthStep + 2 * eqW);j++)
		{
			if(j < eqW)
			{
				flipMat_LeftRight[i * (imgGrayWidthStep + 2 * eqW) + j] = flipMat_UpDown[i * imgGrayWidthStep + (eqW - (j + 1))];
			}
			else if(j >= imgGrayWidthStep + eqW)
			{
				flipMat_LeftRight[i * (imgGrayWidthStep + 2 * eqW) + j] = flipMat_UpDown[i * imgGrayWidthStep + 
																																								(imgGrayWidthStep - (j - imgGrayWidthStep - eqW + 1))];
			}
			else
			{
				flipMat_LeftRight[i * (imgGrayWidthStep + 2 * eqW) + j] = flipMat_UpDown[i * imgGrayWidthStep + (j - eqW)];
			}
		}
	}
	WriteTxt<uchar>("/home/wangli/Limage/flipMat_LeftRight.txt",
									flipMat_LeftRight,
									imgHeight + 2 * eqH,
									imgGrayWidthStep + 2 * eqW);		
}

void CEdgeDete::SobelEdgeDete()
{
	static const int sobel_Gx[9] = {-1,-2,-1,0,0,0,1,2,1};
	static const int sobel_Gy[9] = {-1,0,1,-2,0,2,-1,0,1};

	WriteTxt<uchar>("/home/wangli/Limage/imgGrayMat.txt",
									imgGrayMat,
									imgHeight,
									imgGrayWidthStep);
	FlipMat(imgGrayMat,
				  2,
					3);
}

























