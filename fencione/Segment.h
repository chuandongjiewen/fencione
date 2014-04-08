#pragma once
#include <CString>
#include <map>
#include <fstream>
#include <vector>
#include "SplitStr.h"
using namespace std;

struct SegObjet{
	vector<CString> singleWords; // ���ִ�
	vector<CString> sumWords; // �ܴ���
	vector<CString> nullWords; //���ֵ��
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

