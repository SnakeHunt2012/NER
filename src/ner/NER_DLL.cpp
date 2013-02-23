#define NER_DLL_API_EXPORT
#include "NER_DLL.h"
#include "Model.h"
#include "IRNE7TypeRecog.h"

using namespace std;

CModel pmodel;

int g_isEntity = 1;
int g_isTime = 1;
int g_isNum = 1;

bool* NEtypeFlag;

int LoadResource(const char* path)
{
	string pathname(path);
	pmodel.LoadCRFModel(pathname);
	return 1;
}

void* CreateNErecoger()
{
	IRNErecog *pNER = new IRNErecog(&pmodel);
	return pNER;	
}

void ReleaseNErecoger(void* pNer)
{
	delete (IRNErecog*)pNer;
	delete[] NEtypeFlag;
}

void NERtesting(void* pNer, const wstring& wstrIn, wstring &wstrOut, int tagform)
{
	IRNErecog* pner = (IRNErecog*)pNer;

	NEtypeFlag = new bool[3];
	NEtypeFlag[0] = g_isEntity == 1 ? true : false; 
	NEtypeFlag[1] = g_isTime == 1 ? true : false; 
	NEtypeFlag[2] = g_isNum == 1 ? true : false; 
	
	pner->IRNE7TypeRecog(wstrIn, wstrOut, tagform, NEtypeFlag);
}

void SetNEOption(int isEntity, int isTime, int isNum)
{
	g_isEntity = isEntity;
	g_isTime = isTime;
	g_isNum = isNum;
}