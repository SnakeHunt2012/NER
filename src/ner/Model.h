#ifndef __IR_CModel_H
#define __IR_CModel_H

#include <CRF++/crfpp.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

class CModel
{
public:
	CModel(const char *strModelName="ner.crf") : modelName(strModelName)
	{
		// 以前用ner.med，现在就该为ner.crf吧
	}

	void LoadCRFModel(const std::string& path);
	void ReleaseCRFModel();
private:

public:

	CRFPP::Tagger *pCRFModel;

private:

	std::string modelName;
};
#endif
