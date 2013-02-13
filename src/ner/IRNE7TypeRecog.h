#ifndef __IRNE7TYPERECOG_H__
#define __IRNE7TYPERECOG_H__

#include <string>
#include "Model.h"

using namespace std;

/*
*	����CRF++ʵ��NER����
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