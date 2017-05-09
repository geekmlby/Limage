#ifndef CEDGEDETE_H
#define CEDGEDETE_H

#define MAXLENGTH 1000
#define PI 3.1415926

#define SQUARE(value) (value * value)
#define MAXVALUE(value_a,value_b) (value_a > value_b ? value_a : value_b)
#define MINVALUE(value_a,value_b) (value_a < value_b ? value_a : value_b)

#include"CDIP.h"

class CEdgeDete:public CDIP
{
public:
	CEdgeDete();
	~CEdgeDete();
	void SobelEdgeDete(uchar* matrix_out,
										 uchar* matrix,
										 int height,
										 int width,
										 int thresold);
	void LaplaceEdgeDete(uchar* matrix_out,
										 	 uchar* matrix,
										 	 int height,
										 	 int width,
										 	 int thresold);
	void GaussianBlur(uchar* matrix_out,
										uchar* matrix,
										int height,
										int width,
										int filterH,
										int filterW,
										double sigma);
	void CalConv(uchar* matrix_out,
						   uchar* matrix,
							 int height,
							 int width,
							 int filterH,
							 int filterW,
							 double sigma);
	void CannyEdgeDete(uchar* matrix_out,
										 uchar* matrix,
										 int height,
										 int width,
										 int filterH,
										 int filterW,
										 int upThresold,
										 int downThresold,
										 double sigma);
private:
 
public:
	uchar* edgeMat;
private:

};

#endif




















