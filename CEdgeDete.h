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
	void FlipMat(uchar* matrix,
							 int eqH,
							 int eqW);
public:
	uchar* edgeMat;
	uchar* flipMat_UpDown;
	uchar* flipMat_LeftRight;
private:

};

#endif
