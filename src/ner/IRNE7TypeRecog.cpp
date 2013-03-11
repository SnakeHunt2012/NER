#include "IRNE7TypeRecog.h"
#include <math.h>
#include <string>
#include <tchar.h>
#include <iostream>

using namespace std;

wchar_t target[100][100];

IRNErecog::IRNErecog()
{
}

IRNErecog::IRNErecog(CModel* model)
{
	SetObject(model);
}

IRNErecog::~IRNErecog()
{
	// NOTICE: Here was a bug!!!
	// Cmodel should never be destructed here because it doesn't belong to this IRNErecog object.
	// Bug fixed by Victor.

	//	delete Cmodel;
}

void IRNErecog::SetObject(CModel* model)
{
	this->Cmodel = model;
}

/*
*	It is the interface for NE recognize. The parameter strSen is the input sentense
*  that will deal with, and we will write the result into the outfile. 
*/
void IRNErecog::IRNE7TypeRecog(const wstring& strSen, wstring& StrOut, int tagForm, bool* isNEtypeFlag)
{	
	// 先输出些什么
	wchar_t* str_in = new wchar_t[strSen.length() + 1];
	wcscpy(str_in,strSen.c_str());
	wcout << str_in << endl;

	StrOut = L"输出";
	wchar_t* str_out = new wchar_t[StrOut.length() + 1];
	wcscpy(str_out,StrOut.c_str());
	wcout << str_out << endl;

	//for (int i = 0; i < strSen.length(); ++i) {
		//wcout << str_in[i] << endl;
		//wprintf(L"%d:\t%c\t%x\n", i, str_in[i], str_in[i]);

	//}

	int i = 0;
	int j = 0;
	int k = 0;
	char *CStr;
	Cmodel->pCRFModel->clear(); 

	
	// 格式化送入CRF++
	DWORD n;
	while (i <= (int)strSen.length()) {
		if (str_in[i] == L'/')
			target[k][j++] =  L' ';
		else if (str_in[i] == L' ') {
			target[k][j] = L'\0';
			n=WideCharToMultiByte(CP_OEMCP,NULL, target[k],-1,NULL,0,NULL,FALSE);
			char *CStr=new char[n];
			WideCharToMultiByte(CP_OEMCP,NULL, target[k],-1, CStr,n,NULL,FALSE);

			Cmodel->pCRFModel->add(CStr);
			delete [] CStr;
			j = 0;
		}
		else 
			target[k][j++] = str_in[i];
		i++;
	}

	if (!Cmodel->pCRFModel->parse())
		cout << "Parse Error!!!" << endl;

	cout << "size: " << Cmodel->pCRFModel->size() << endl;

	/* debug: CRF++的处理结果
	for (i = 0; i < Cmodel->pCRFModel->size(); ++i) {
		cout << i << ": ";
		for (j = 0; j < Cmodel->pCRFModel->xsize(); ++j) {
			cout << Cmodel->pCRFModel->x(i, j) << '\t';
		}
		cout << Cmodel->pCRFModel->y2(i) << '\t';
		cout << endl;
	}
	*/


	// CRF++输出格式化
	char result[1024];
	j = 0;
	for(i = 0; i < Cmodel->pCRFModel->size(); ++i) {


			if (*(Cmodel->pCRFModel->y2(i)) == 'B') {

					result[j++] = '[';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 0) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 0) + k);
						k++;
					}
					result[j++] = '/';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 1) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 1) + k);
						k++;
					}
					result[j++] = ' ';

			} else if (*(Cmodel->pCRFModel->y2(i)) == 'I') {

					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 0) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 0) + k);
						k++;
					}
					result[j++] = '/';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 1) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 1) + k);
						k++;
					}
					result[j++] = ' ';

			} else if (*(Cmodel->pCRFModel->y2(i)) == 'E') {

					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 0) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 0) + k);
						k++;
					}
					result[j++] = '/';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 1) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 1) + k);
						k++;
					}
					result[j++] = ']';
					k = 2;
					while(*(Cmodel->pCRFModel->y2(i) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->y2(i) + k);
						k++;
					}
					result[j++] = ' ';

			} else if (*(Cmodel->pCRFModel->y2(i)) == 'S') {

					result[j++] = '[';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 0) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 0) + k);
						k++;
					}
					result[j++] = '/';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 1) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 1) + k);
						k++;
					}
					result[j++] = ']';
					k = 2;
					while(*(Cmodel->pCRFModel->y2(i) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->y2(i) + k);
						k++;
					}
					result[j++] = ' ';

			} else if (*(Cmodel->pCRFModel->y2(i)) == 'O') {

					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 0) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 0) + k);
						k++;
					}
					result[j++] = '/';
					k = 0;
					while(*(Cmodel->pCRFModel->x(i, 1) + k) != '\0') {
						result[j++] = *(Cmodel->pCRFModel->x(i, 1) + k);
						k++;
					}
					result[j++] = ' ';

			}
	}
	result[j] = '\0';
	cout << result << endl;

	// char 转 wchar_t
	size_t len = strlen(result) + 1;
	size_t converted = 0;
	wchar_t *WStr;
	WStr = (wchar_t *)malloc(len * sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, result, _TRUNCATE);
	wcout << WStr << endl;

	// wchar_t[] 转 wstring
	StrOut.assign(WStr);

	wcout << StrOut << endl;

	return;
}