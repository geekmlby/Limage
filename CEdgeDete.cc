#include"CEdgeDete.h"
#include<stdio.h>
#include<iostream>

CEdgeDete::CEdgeDete()
{
	edgeMat = NULL;
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
	WriteTxt<uchar>("/home/wangli/Limage/UpDown.txt",
									tmpMat,
									height + 2 * eqH,
									width);
	
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
	WriteTxt<uchar>("/home/wangli/Limage/flippedMat.txt",
									matrix_out,
									height + 2 * eqH,
									width + 2 * eqW);

	delete tmpMat;
	tmpMat = NULL;
}

/*void CEdgeDete::CalConv(uchar* matrix_out,   //Calculate convolution
							 					uchar* matrix,
							 					int* operMat_Gx,
							 					int* operMat_Gy,
												int height,
												int width,
												int operH,
							 					int operW)
{
	int i,j;

	for(i = operH / 2;i < height + (operH / 2) - 1;i++)
	{
		for(j = operW / 2;j < width + (operW / 2) - 1;j++)
		{
			matrix_out[(i - operH / 2) * width + ]
		}
	}
}*/

void CEdgeDete::SobelEdgeDete()
{
	static const int sobel_Gx[9] = {-1,-2,-1,0,0,0,1,2,1};
	static const int sobel_Gy[9] = {-1,0,1,-2,0,2,-1,0,1};

	WriteTxt<uchar>("/home/wangli/Limage/imgGrayMat.txt",
									imgGrayMat,
									imgHeight,
									imgGrayWidthStep);
	uchar* flippedMat;
	uchar* convMat;

	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];
	convMat = new uchar[MAXHEIGHT * MAXWIDTH];

	/*FlipMat(flippedMat,
					imgGrayMat,
					imgHeight,
					imgGrayWidthStep,
				  1,
					1);*/
}

























