/*CDIP类，Digital Image Process数字图像处理类。
 包含基本的图像处理算法。
*/

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

#define PI          3.1415926
#define PATHSIZE	100
#define MAXHEIGHT	2000
#define MAXWIDTH	2000
#define MAXLENGTH   1000

#define SQUARE(value) (value * value)
#define MAXV(value_x,value_y) (value_x > value_y ? value_x : value_y)
#define MINV(value_x,value_y) (value_x < value_y ? value_x : value_y)

class CDIP
{
public:
    CDIP();
    ~CDIP();
    void ReadImage(char* path);
    void ShowImage();
    void ShowImage(const char* windowName,
             	   uchar* Mat,
		           int h,
		           int w,
		           int depth = 8,
		           int channels = 1);
    void GetImageRGB();
    void GetGrayImage();

	template<class type>
	void WriteTxt(const char* txtName,
		          type* Mat,
		          int h,
		          int w)
	{
        int i,j;
		FILE *fp;
		fp = fopen(txtName,"wb");
		for (i = 0;i < h;i++)
		{
			for (j = 0;j < w;j++)
			{
				fprintf(fp,"%4d ",Mat[i * w + j]);   //Because of "%d ",the template is only useful to "int","char" and "uchar".
			}
			fprintf(fp,"\n");
		}
		fclose(fp);		
	}

	void FlipMat(uchar* Mat_out,
		         uchar* Mat,
		         int h,
		         int w,
		         int filterH,
		         int filterW);

    void EdgeDete_Sobel(uchar* Mat_out,
                        uchar* Mat,
                        int h,
                        int w,
                        int thre);
    void EdgeDete_Laplace(uchar* Mat_out,
                          uchar* Mat,
                          int h,
                          int w,
                          int thre);
    void EdgeDete_Canny(uchar* Mat_out,
                        uchar* Mat,
                        int h,
                        int w,
                        int filterH,
                        int filterW,
                        int upThre,
                        int downThre,
                        double sigma);
    void GaussianBlur(uchar* Mat_out,
                      uchar* Mat,
                      int h,
                      int w,
                      int filterH,
                      int filterW,
                      double sigma);
    void Calconv(uchar* Mat_out,
                 uchar* Mat,
                 int h,
                 int w,
                 int filterH,
                 int filterW,
                 double sigma);
private:

public:
    int imgH;
	int imgW;
	int imgChannels;
	int imgDepth;
	int imgSize;
	int imgWidthStep;
	uchar* puc_imgData;
	uchar* puc_imgRMat;
	uchar* puc_imgGMat;
	uchar* puc_imgBMat;
	uchar* puc_imgGrayMat;
	uchar* edgeMat;
private:
	IplImage* pImg_srcImg;
};

#endif

























