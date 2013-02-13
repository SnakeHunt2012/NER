#ifndef __IRNE7TYPERECOG_H__
#define __IRNE7TYPERECOG_H__

#include <string>
#include "Model.h"

using namespace std;

/*
*	利用CRF++实现NER过程
*/

class IRNErecog
{
public:

	IRNErecog();
	IRNErecog(CModel* model);

	virtual ~IRNErecog();
	void SetObject(CModel* model);
	void IRNE7TypeRecog(const wstring& strSen, wstring& StrOut, int tagForm, bool* isNEtypeFlag);

private:

	CModel* Cmodel;
};
#endif