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
	delete flippedMat;
	flippedMat = NULL;
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
			if(edgeMat[i * imgGrayWidthStep + j] > 130)
			{
				edgeMat[i * imgGrayWidthStep + j] = 255;
			}
			else
			{
				edgeMat[i * imgGrayWidthStep + j] = 0;
			}
		}
	}
	WriteTxt<uchar>("/home/wangli/Limage/edgeMat.txt",
									edgeMat,
									imgHeight,
									imgGrayWidthStep);
	delete flippedMat;
	delete tmpArray;
	flippedMat = NULL;
	tmpArray = NULL;
}

void CEdgeDete::GaussianBlur()
{
	double sigma;
	int filterH,filterW;
	int eqH,eqW;
	double sum;
	uchar* flippedMat;
	double* gaussianMat;
	double* weightArray;
	double* tmpArray;

	sigma = 1.5;
	filterH = 3;
	filterW = 3;
	sum = 0;
	eqH = filterH / 2;
	eqW = filterW / 2;
	flippedMat = new uchar[MAXHEIGHT * MAXWIDTH];	
	gaussianMat = new double[MAXHEIGHT * MAXWIDTH];
	weightArray = new double[MAXLENGTH];
	tmpArray = new double[MAXLENGTH];

	memset(gaussianMat,0,MAXHEIGHT * MAXWIDTH);
	FlipMat(flippedMat,
					imgGrayMat,
					imgHeight,
					imgGrayWidthStep,
				  1,
					1);
	for(int x = (-1 * (filterH / 2));x < ((filterH / 2) + 1);x++)
	{
		for(int y = (-1 * (filterW / 2));y < ((filterW / 2) + 1);y++)
		{
			weightArray[(x + (filterH / 2)) * filterW + (y + (filterW / 2))] 
			= exp(-1 * (SQUARE(x) + SQUARE(y)) / (2 * SQUARE(sigma))) / (2 * PI * SQUARE(sigma));
			sum = sum + weightArray[(x + (filterH / 2)) * filterW + (y + (filterW / 2))];
			//cout << "The weight is: " << weightArray[(x + (filterH / 2)) * filterW + (y + (filterW / 2))] << endl;
		}
	}
	//cout << "The sum is: " << sum << endl;
	for(int i = 0;i < (filterH * filterW);i++)
	{
		weightArray[i] = weightArray[i] / sum;
		//cout << "The weight is: " << weightArray[i] << endl;
	}
	for(int i = 1;i < imgHeight + 1;i++)
	{
		for(int j = 1;j < imgGrayWidthStep + 1;j++)
		{
			for(int x = (-1 * (filterH / 2));x < ((filterH / 2) + 1);x++)
			{
				for(int y = (-1 * (filterW / 2));y < ((filterW / 2) + 1);y++)
				{
					tmpArray[(x + eqH) * filterW + (y + eqW)] = flippedMat[(i + x) * (imgGrayWidthStep + 2 * eqW) + (j + y)];
					/*cout << "The index is: " << (x + eqH) * filterW + (y + eqW) << endl;
					cout << "The tmpArray is: " << tmpArray[(x + eqH) * filterW + (y + eqW)] << endl;*/
				}
			}	
			//cout << "**************************************************************************************************************" << endl;
			for(int k = 0;k < (filterH * filterW);k++)
			{
				gaussianMat[(i - 1) * imgGrayWidthStep + (j - 1)] += (tmpArray[k] * weightArray[k]);
				/*cout << "The tmpArray is: " << tmpArray[k] << endl;
				cout << "The weightArray is: " << weightArray[k] << endl;*/
			}		
			gaussianMat[(i - 1) * imgGrayWidthStep + (j - 1)] = (int)gaussianMat[(i - 1) * imgGrayWidthStep + (j - 1)];
			edgeMat[(i - 1) * imgGrayWidthStep + (j - 1)] = (uchar)gaussianMat[(i - 1) * imgGrayWidthStep + (j - 1)];;
			/*cout << "The gaussianMat is: " << gaussianMat[(i - 1) * imgGrayWidthStep + (j - 1)] << endl;
			cout << "The uchar gaussianMat is: " << (int)gaussianMat[(i - 1) * imgGrayWidthStep + (j - 1)] << endl;
			cout << "The edgeMat is: " << edgeMat[(i - 1) * imgGrayWidthStep + (j - 1)] << endl;
			cout << "**************************************************************************************************************" << endl;*/
		}
	}
	ShowImage("GaussianBlurImage",
						edgeMat,
						imgHeight,
						imgWidth);
	/*WriteTxt<uchar>("/home/wangli/Limage/gaussianMat.txt",
									gaussianMat,
									imgHeight,
									imgGrayWidthStep);*/

	delete flippedMat;
	delete gaussianMat;
	delete weightArray;
	delete tmpArray;
	flippedMat = NULL;
	gaussianMat = NULL;
	weightArray = NULL;
	tmpArray = NULL;
}





















