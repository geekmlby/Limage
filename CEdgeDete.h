#ifndef CEDGEDETE_H
#define CEDGEDETE_H

#include"CDIP.h"

class CEdgeDete:public CDIP
{
public:
	CEdgeDete();
	~CEdgeDete();
	void Sobel();
private:

public:
	int Gx;
	int Gy;
	uchar* edgeMat;
private:

};

#endif
