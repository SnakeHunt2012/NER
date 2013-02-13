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
		// ��ǰ��ner.med�����ھ͸�Ϊner.crf��
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
