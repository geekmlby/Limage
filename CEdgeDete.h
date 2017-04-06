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

public:
	uchar* edgeMat;
private:

};

#endif
