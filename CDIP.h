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
	void ReadImage(char* imagePath_in);
	int GetHeight();
	int GetWidth();
	void ShowImage();
	void GetImageRGB();
	void GetGrayImage();
	void WriteTxt_char(const char* pcName,
										 const char* pucMatrix,
										 int h,
										 int w);
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
				fprintf(fp,"%d ",pMatrix[i * w + j]);   //Because of "%d ",the template is only useful to "int" and "char" or maybe "uchar".
			}
			fprintf(fp,"\n");
		}
		fclose(fp);		
	}

	/*template<class type>   //This is a test function template.
	void GetMax(type a,
							type b)
	{
		if(a > b)
			cout << "The max value is:" << a << endl;
		else
			cout << "The max value is:" << b << endl;
	}*/
private:

public:
	IplImage* grayImg;
private:
	IplImage* srcImg;
	uchar* blueComp;
	uchar* greenComp;
	uchar* redComp;
};

#endif

























