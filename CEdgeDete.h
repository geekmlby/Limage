#ifndef CEDGEDETE_H
#define CEDGEDETE_H

#define MAXLENGTH 100
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
	void SobelEdgeDete();
	void LaplaceEdgeDete();
	void GaussianBlur();
private:
 
public:
	uchar* edgeMat;
private:

};

#endif
