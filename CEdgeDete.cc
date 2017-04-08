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
							 					int height,
							 					int width,
							 					int eqH,
							 					int eqW)
{
	int i,j;
	flipMat_UpDown = new uchar[MAXHEIGHT * MAXWIDTH];
	flipMat_LeftRight = new uchar[MAXHEIGHT * MAXWIDTH];

	for(i = 0;i < eqH;i++)
	{
		memcpy(flipMat_UpDown + i * width,matrix + (eqH - (i + 1)) * width,width);
	}
	memcpy(flipMat_UpDown + eqH * width,matrix,height * width);
	for(i = height + eqH;i < height + 2 * eqH;i++)
	{
		memcpy(flipMat_UpDown + i * width,matrix + (height - (i - height - eqH + 1)) * width,width);
	}
	WriteTxt<uchar>("/home/wangli/Limage/flipMat_UpDown.txt",
									flipMat_UpDown,
									6,
									4);		
	for(i = 0;i < height + 2 * eqH;i++)
	{								
		for(j = 0;j < (width + 2 * eqW);j++)
		{
			if(j < eqW)
			{
				flipMat_LeftRight[i * (width + 2 * eqW) + j] = flipMat_UpDown[i * width + (eqW - (j + 1))];
			}
			else if(j >= width + eqW)
			{
				flipMat_LeftRight[i * (width + 2 * eqW) + j] = flipMat_UpDown[i * width + (width - (j - width - eqW + 1))];
			}
			else
			{
				flipMat_LeftRight[i * (width + 2 * eqW) + j] = flipMat_UpDown[i * width + (j - eqW)];
			}
		}
	}
	WriteTxt<uchar>("/home/wangli/Limage/flipMat_LeftRight.txt",
									flipMat_LeftRight,
									6,
									8);		
}

void CEdgeDete::SobelEdgeDete()
{
	static const int sobel_Gx[9] = {-1,-2,-1,0,0,0,1,2,1};
	static const int sobel_Gy[9] = {-1,0,1,-2,0,2,-1,0,1};

	uchar testArray[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	WriteTxt<uchar>("/home/wangli/Limage/testArray.txt",
									testArray,
									4,
									4);
	FlipMat(testArray,
					4,
					4,
				  1,
					2);
}

























