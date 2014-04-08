#pragma once
#include <CString>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include "SplitStr.h"
using namespace std;

struct WordItem{
	int start;
	int end;
	CString word;
	double frequency; //�ڴʵ��еĸ���
	double multiFrequency; //�ۼƸ���
	WordItem *bestLeftWord; //keyΪ���ڴʣ�valueΪ���ڴʵ��ۼƸ���
	CString leftWord;

	bool operator()(const WordItem &item1, const WordItem &item2)
	{
		return item1.multiFrequency > item2.multiFrequency;
	}
	
};


struct DictItem{
	int num;
	double frequency;
};

class CstatisticSeg
{
public:
	CstatisticSeg(void);
	virtual ~CstatisticSeg(void);
	void loadDict(CString dictPath);
	CString doCut(CString sentence);
	void init();
	
	//bool compareWord(const WordItem &item1, const WordItem &item2);

public:
	int dictTime;
	int cutTime;

private:
	map<CString, DictItem> dictionary;//�ʵ�
	map<CString, WordItem> sourceWordMap;//key �浱ǰ
	map<int, vector<WordItem>> leftWordMap;
	
	WordItem lastWord;

	double calMultiFrequency(WordItem *wordItem);
	CString output();

};

