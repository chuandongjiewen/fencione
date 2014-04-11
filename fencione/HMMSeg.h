#pragma once
#include <CString>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <afx.h>
#include "SplitStr.h"

using namespace std;

//转移概率的每一项
struct POS{
	CString iPos;//前项
	CString jPos;//后项
	int num;
	double frequency;
};

//转移概率矩阵的每一行
struct ListPOS{
	map<CString, POS*> posMap;//后项为key的词的列表
	int sum;//所有标注的总和
};

class CHMMSeg
{

private:
	map<CString, ListPOS*> transition;//转移概率
	map<CString, ListPOS*> emission;//发射概率
	vector<CString> wordsVect;

public:
	CHMMSeg(void);
	~CHMMSeg(void);
	
	void init();
	//---------------转移概率的计算----------------------------------------------
	void processTransition(CString dictPath);//从199801.txt中提取原始信息
	void calTransition(int m, double p);//计算转移概率, m 用户指定的数目 4， p为指定的概率(0.5)
	void writeTransition(CString path);
	void readTransition(CString path);
	POS* createTransitionPos(CString iPos, CString jPos);//创建一个词性标注对象，如果存在则修改Num+1


	//---------------发射概率的计算----------------------------------------------
	void processEmission(CString dictPath);
	POS* createEmissionPos(CString iPos, CString jPos);// ipos 为词项，jPos为词性
	void calEmission(int m, double p);
	void writeEmission(CString path);
};


