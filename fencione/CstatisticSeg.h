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
	double frequency; //在词典中的概率
	double multiFrequency; //累计概率
	WordItem *bestLeftWord; //key为左邻词，value为左邻词的累计概率
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
	map<CString, DictItem> dictionary;//词典
	map<CString, WordItem> sourceWordMap;//key 存当前
	map<int, vector<WordItem>> leftWordMap;
	
	WordItem lastWord;

	double calMultiFrequency(WordItem *wordItem);
	CString output();

};

