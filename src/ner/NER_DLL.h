#ifndef __NER_DLL_H__
#define __NER_DLL_H__

#define NER_DLL_API

#include <vector>
#include <string>

using namespace std;

void NERecog(void* NETagger, const std::vector<std::string>& vecWord, const std::vector<std::string>& vecPOS, std::vector<std::string>& vecResult);

//load Resource
NER_DLL_API int LoadResource(const char* path);

//create an object for Convert Code
NER_DLL_API void* CreateNErecoger();

//release Converter
NER_DLL_API void ReleaseNErecoger(void* pNer);

//NER_DLL_API void ReleaseResource();

NER_DLL_API void SetNEOption(int isEntity, int isTime, int isNum);

//NER_DLL_API void NERtesting(void* pNer, wchar_t* pwstrIn, wchar_t* pwstrOut, int tagform);
NER_DLL_API void NERtesting(void* pNer, const std::wstring& wstrIn, std::wstring & wstrOut, int tagform);

//NER_DLL_API void MixedNER(void* const pNer, void* const pTrieDict, void* const pTimePattern, const std::wstring& wstrIn, std::wstring& wstrOut, const int ntagform);

#endif
