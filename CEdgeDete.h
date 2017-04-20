#ifndef CEDGEDETE_H
#define CEDGEDETE_H

#define SQUARE(value) (value * value)
#define MAXVALUE(value_a,value_b) (value_a > value_b ? value_a : value_b)
#define MINVALUE(value_a,value_b) (value_a < value_b ? value_a : value_b)

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
