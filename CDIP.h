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
								type * matrix,
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

private:

public:
	int imgHeight;
	int imgWidth;
	uchar* imgBMat;
	uchar* imgGMat;
	uchar* imgRMat;
	uchar* imgGrayMat;
	int imgGrayWidthStep;
private:
	IplImage* srcImg;
};

#endif

























