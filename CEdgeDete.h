#ifndef CEDGEDETE_H
#define CEDGEDETE_H

#include"CDIP.h"

class CEdgeDete:public CDIP
{
public:
	CEdgeDete();
	~CEdgeDete();
	void SobelEdgeDete();
private:
	void FlipMat(uchar* matrix_out,
							 uchar* matrix,
							 int height,
							 int width,
							 int eqH,
							 int eqW);
	/*void CalConv(uchar* matrix_out,   //Calculate convolution
							 uchar* matrix,
							 int* operMat_Gx,
							 int* operMat_Gy,
							 int height,
							 int width,
							 int operH,
							 int operW);*/   
public:
	uchar* edgeMat;
private:

};

#endif
