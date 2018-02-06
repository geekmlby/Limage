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
	static void WriteTxt(const char* txtName,     //可以定义成静态函数，不用CDIP类对象，可以直接用类名调用。
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
				fprintf(fp,"%4d ",Mat[i * w + j]);     //因为“%d”，这个模板只适用于“int”，“char”和“uchar”。
			}
			fprintf(fp,"\n");
		}
		fclose(fp);		
	}

	template<class type>
	static void FlipMat(type* Mat_out,
						type* Matrix,
						int h,
						int w,
						int filH,
						int filW)
	{
		int i,j;
		int eqH,eqW;
		type* pty_tmpMat = NULL;

		eqH = filH / 2;
		eqW = filW / 2;
		pty_tmpMat = new type[MAXHEIGHT * MAXWIDTH];

		if(h <= 0 || w <= 0 || eqH > h || eqW > w)
		{
			cout << "The input parameters error!" << endl;
			return;
		}

		//Flip vertical
		for(i = 0;i < eqH;i++)
		{
			memcpy(pty_tmpMat + i * w,Matrix + (eqH - (i + 1)) * w,w);
		}
		memcpy(pty_tmpMat + eqH * w,Matrix,h * w);
		for(i = h + eqH;i < h + 2 * eqH;i++)
		{
			memcpy(pty_tmpMat + i * w,Matrix + (h - (i - h - eqH + 1)) * w,w);
		}
		//Flip horizontal
		for(i = 0;i < h + 2 * eqH;i++)
		{								
			for(j = 0;j < (w + 2 * eqW);j++)
			{
				if(j < eqW)
				{
			    	Mat_out[i * (w + 2 * eqW) + j] = pty_tmpMat[i * w + (eqW - (j + 1))];
				}
				else if(j >= w + eqW)
				{
					Mat_out[i * (w + 2 * eqW) + j] = pty_tmpMat[i * w + (w - (j - w - eqW + 1))];
				}
				else
				{
					Mat_out[i * (w + 2 * eqW) + j] = pty_tmpMat[i * w + (j - eqW)];
				}
			}
		}

		delete pty_tmpMat;
		pty_tmpMat = NULL;
	}

    void EdgeDete_Sobel(uchar* Matrix,
                        int h,
                        int w,
                        int thre);
	void EdgeDete_Laplace(uchar* Matrix,
                          int h,
                          int w,
					      int thre);
    void GausBlur(uchar* Matrix,
                  int h,
                  int w,
                  int filH,
                  int filW,
                  double sigma);
	void CalConv(uchar* Matrix,     //因为计算卷积的时候，有可能输出负值，uchar数组中的数据会出现错误，所以这个函数要慎用。
				 double* Wei,
                 int h,
                 int w,
                 int filH,
                 int filW);

private:

public:
	int imgH;
	int imgW;     //图像的宽度
	int actW;     //图像的实际宽度，是4的倍数。
	int imgDepth;
	int imgChannel;	
	int imgSize;
	int imgWidthStep;
	uchar* puc_imgData;
	
private:
	IplImage* pImg_src;
};

#endif

























