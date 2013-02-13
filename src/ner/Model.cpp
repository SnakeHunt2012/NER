#include "Model.h"
#include <string>

void CModel::ReleaseCRFModel()
{
}

void CModel::LoadCRFModel(const string& path)
{
	string model = path + "/" + modelName;
	string paramenter = "-m " + model + " -v 3 -n2";
	pCRFModel = CRFPP::createTagger(paramenter.c_str());
}