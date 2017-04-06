#include"CEdgeDete.h"
#include<stdio.h>
#include<iostream>

CEdgeDete::CEdgeDete()
{
}

CEdgeDete::~CEdgeDete()
{
}

void CEdgeDete::SobelEdgeDete()
{
	int Gx,Gy;
	uchar* flipMat_UpDown;
	uchar* flipMat_LeftRight;

	uchar testArray[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	WriteTxt<uchar>("/home/wangli/Limage/testArray.txt",
								  testArray,
									4,
									4);

	flipMat_UpDown = new uchar[MAXHEIGHT * MAXWIDTH];
	flipMat_LeftRight = new uchar[MAXHEIGHT * MAXWIDTH];
	edgeMat = new uchar[MAXHEIGHT * MAXWIDTH];
	memset(edgeMat,MAXHEIGHT * MAXWIDTH,0);

	memcpy(flipMat_UpDown,testArray,4);
	memcpy(flipMat_UpDown + 4,testArray,16);
	memcpy(flipMat_UpDown + 4 + 16,testArray + 4 * 3,4);
	WriteTxt<uchar>("/home/wangli/Limage/flipMat_UpDown.txt",
								  flipMat_UpDown,
									6,
									4);
	for(int i = 0;i < 6;i++)
	{
		for(int j = 0;j < 6;j++)
		{
			if(0 == j)
			{
				flipMat_LeftRight[i * 6 + j] = flipMat_UpDown[i * 4 + j];
			}
			else if((6 - 1) == j)
			{
				flipMat_LeftRight[i * 6 + j] = flipMat_UpDown[i * 4 + (j - 2)];				
			}
			else
			{
				flipMat_LeftRight[i * 6 + j] = flipMat_UpDown[i * 4 + (j - 1)];
			}
		}
	}
	WriteTxt<uchar>("/home/wangli/Limage/flipMat_LeftRight.txt",
								  flipMat_LeftRight,
									6,
									6);
}

























