/*CDIP，Digital Image Process数字图像处理类。
 包含基本的数字图像处理算法。
*/

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#ifndef CDIP_H
#define CDIP_H

#define PI          3.1415926
#define PATHSIZE	100   //文件路径的最大值
#define MAXLENGTH   1000
#define MAXHEIGHT	2000
#define MAXWIDTH	2000

#define SQUAREV(value) (value * value)
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
             	   uchar* Matrix,
		           int h,
		           int w,
		           int depth = 8,
		           int channel = 1);
    void GetRGBImage(uchar* RMat,
					 uchar* GMat,
					 uchar* BMat);
    void GetGrayImage(uchar* GrayMat);

	template<class type>
	void WriteTxt(const char* txtName,
		          type* Mat,
		          int h,
		          int w)
	{
        int i,j;
		FILE* fp;
		fp = fopen(txtName,"wb");
		for (i = 0;i < h;i++)
		{
			for (j = 0;j < w;j++)
			{
				fprintf(fp,"%4d ",Mat[i * w + j]);     //注：因为“%d”，这个模板只适用于“int”，“char”和“uchar”。
			}
			fprintf(fp,"\n");
		}
		fclose(fp);		
	}

	static void FlipMat(uchar* Mat_out,
		         		uchar* Matrix,
		         		int h,
		         		int w,
		         		int filterH,
		         		int filterW);

    void EdgeDete_Sobel(uchar* Mat_out,
                        uchar* Matrix,
                        int h,
                        int w,
                        int thre);
    void EdgeDete_Laplace(uchar* Mat_out,
                          uchar* Matrix,
                          int h,
                          int w,
                          int thre);
    void EdgeDete_Canny(uchar* Mat_out,
                        uchar* Matrix,
                        int h,
                        int w,
                        int filterH,
                        int filterW,
                        int upThre,
                        int downThre,
                        double sigma);

    void GaussianBlur(uchar* Mat_out,
                      uchar* Matrix,
                      int h,
                      int w,
                      int filterH,
                      int filterW,
                      double sigma);
    void Calconv(uchar* Mat_out,
                 uchar* Matrix,
                 int h,
                 int w,
                 int filterH,
                 int filterW,
                 double sigma);
private:

public:
	int imgH;
	int imgW;
	int imgDepth;
	int imgChannel;	
	int imgSize;
	int imgWidthStep;
	uchar* puc_imgData;
	
private:
	IplImage* pImg_src;
};

#endif

























