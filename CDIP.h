#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

#define PATHSIZE		100
#define MAXHEIGHT		1080
#define MAXWIDTH		1920

class CDIP
{
public:
  CDIP();
  ~CDIP();
	void ReadImage(char* imagePath);
	void ShowImage();
	void ShowImage(const char* windowName,
								 uchar* imgMat,
								 int h,
								 int w,
								 int depth = 8,
								 int channels = 1);
	void GetImageRGB();
	void GetGrayImage();

	template<class type>
	void WriteTxt(const char* pcName,
								type * pMatrix,
								int h,
								int w)
	{
		int i,j;
		FILE *fp;
		fp = fopen(pcName,"wb");
		for (i = 0;i < h;i++)
		{
			for (j = 0;j < w;j++)
			{
				fprintf(fp,"%d ",pMatrix[i * w + j]);   //Because of "%d ",the template is only useful to "int","char" and "uchar".
			}
			fprintf(fp,"\n");
		}
		fclose(fp);		
	}
private:

public:
	int imgHeight;
	int imgWidth;
	uchar* blueMat;
	uchar* greenMat;
	uchar* redMat;
	uchar* grayMat;
	IplImage* srcImg;
private:

};

#endif

























