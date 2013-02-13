#include "IRNE7TypeRecog.h"
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

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
	wcout << strSen << endl;
}