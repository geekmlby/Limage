#ifndef CEDGEDETE_H
#define CEDGEDETE_H

#define SQUARE(Value) (Value * Value)

#include"CDIP.h"

class CEdgeDete:public CDIP
{
public:
	CEdgeDete();
	~CEdgeDete();
	void SobelEdgeDete();
	void LaplaceEdgeDete();
private:
	void FlipMat(uchar* matrix_out,
							 uchar* matrix,
							 int height,
							 int width,
							 int eqH,
							 int eqW);  
public:
	uchar* edgeMat;
private:

};

#endif
