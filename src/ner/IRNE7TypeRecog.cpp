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
	
	while (i <= (int)strSen.length()) {
		if (str_in[i] == L'/')
			target[k][j++] =  L'\t';
		else if (str_in[i] == L' ') {
			target[k][j] = L'\0';

			size_t len = wcslen(target[k]) + 1;
			size_t converted = 0;
			CStr=(char*)malloc(len*sizeof(char));
			wcstombs_s(&converted, CStr, len, target[k++], _TRUNCATE);

			Cmodel->pCRFModel->add(CStr);
			wcout << target[k - 1] << endl;
			j = 0;
		}
		else 
			target[k][j++] = str_in[i];
		i++;
	}

	Cmodel->pCRFModel->parse();

	for (size_t i = 0; i < Cmodel->pCRFModel->ysize(); ++i) {
		std::cout << "tag " << i << " " << Cmodel->pCRFModel->yname(i) << std::endl;
	}

	/* test

	Cmodel->pCRFModel->clear(); 

	Cmodel->pCRFModel->add("我 n");
	Cmodel->pCRFModel->add("是 v");
	Cmodel->pCRFModel->add("谁 n");

	Cmodel->pCRFModel->parse();

	cout << Cmodel->pCRFModel->y2(1) << endl;
	cout << Cmodel->pCRFModel->y2(2) << endl;
	*/
}