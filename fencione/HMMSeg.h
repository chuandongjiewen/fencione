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


class CHMMSeg
{

private:
	map<CString, POS*> initialization;//初始概率,key为词性标注
	int sumOfInit; //初始的总和

	map<CString, POS*> transition;//转移概率 key为词性标注
	map<CString, int> sumLineTran;// 转移概率每一行的sum

	map<CString, POS*> emission;//发射概率 key为词性标注
	map<CString, int> sumLineEmission; //发射概率每一行的sum

	vector<CString> posVect; //所有词性标注的集合 存所有词性标注
	vector<CString> wordsVect;//所有词的集合 存所有的单词

public:
	CHMMSeg(void);
	~CHMMSeg(void);
	
	void init();
	//---------------初始概率的计算----------------------------------------------
	void processInitial(CString dictPath);
	void calInitial(int m, double p);
	void writeInitial(CString path);

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


