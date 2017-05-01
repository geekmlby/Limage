#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

#define PATHSIZE		100
#define MAXHEIGHT		2000
#define MAXWIDTH		2000

class CDIP
{
public:
  CDIP();
  ~CDIP();
	void ReadImage(char* path);
	void ShowImage();
	void ShowImage(const char* windowName,
								 uchar* matrix,
								 int height,
								 int width,
								 int depth = 8,
								 int channels = 1);
	void GetImageRGB();
	void GetGrayImage();

	template<class type>
	void WriteTxt(const char* txtName,
								type* matrix,
								int height,
								int width)
	{
		int i,j;
		FILE *fp;
		fp = fopen(txtName,"wb");
		for (i = 0;i < height;i++)
		{
			for (j = 0;j < width;j++)
			{
				fprintf(fp,"%4d ",matrix[i * width + j]);   //Because of "%d ",the template is only useful to "int","char" and "uchar".
			}
			fprintf(fp,"\n");
		}
		fclose(fp);		
	}

	void FlipMat(uchar* matrix_out,
							 uchar* matrix,
							 int height,
							 int width,
							 int eqH,
							 int eqW); 
private:

public:
	int imgHeight;
	int imgWidth;
	int imgChannels;
	int imgDepth;
	int imgSize;
	int imgWidthStep;
	uchar* imgData;
	uchar* imgRMat;
	uchar* imgGMat;
	uchar* imgBMat;
	uchar* imgGrayMat;
private:
	IplImage* srcImg;
};

#endif

























