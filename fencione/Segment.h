#pragma once
#include <CString>
#include <map>
#include <fstream>
#include <vector>
#include "SplitStr.h"
using namespace std;

struct SegObjet{
	vector<CString> singleWords; // 单字词
	vector<CString> sumWords; // 总词数
	vector<CString> nullWords; //非字典词
};

class CSegment
{
private:
	int maxLen;
	CString sentence;
	map<CString, CString> dictionary;

public:
	SegObjet pResult;
	SegObjet nResult;

	int pTime;
	int nTime;
	int dictTime;

public:
	CSegment(int maxLen);
	virtual ~CSegment();
	void init();
	void setMaxLen(int maxLen);
	void loadDict(CString dictPath);
	CString MMPositive(CString sentence);
	CString MMNegative(CString sentence);
	CString MMDouble(CString sentence);

private:
	int ExtString(CString str, CStringArray &strArray);

};

