#pragma once
#include <CString>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <afx.h>
#include "SplitStr.h"
#include "HMMSeg.h"
using namespace std;

struct Vet{
	int id; //当前词的id
	double frequency; //累计概率
	CString word; //词的内容
	CString pos; //词性标注
	Vet *preVet; //前驱结点
};

class CHmm
{

public:
	double m; //m估计的值 默认10
	double p; //m估计的概率 默认0.5

public:

	vector<CString> posVect; // 所有词性标注的集合
	vector<CString> wordsVect; //所有待分的词的集合

	map<CString, POS*> emissionMap;
	map<CString, POS*> transitionMap;
	map<CString, POS*> initMap;

	map<CString, int> sumOfEm; //每一行发射概率的和
	map<CString, int> sumOfTran;//每一行转移概率的和

	//存储所有路线的 key: id,word,pos 
	map<CString, Vet*> resultMap;
	vector<Vet*> lastVetVector;
	Vet *maxLastVet;

public:
	CHmm(void);
	virtual ~CHmm(void);

	void loadEmission(CString path);
	void loadTransition(CString path);
	void loadInit(CString path);

	void init();
	void calculate();
	void setEstimate(int m, double p);//设置m估计的数据平滑
	void setWords(vector<CString> data);
	CString output();

private: 
	void reset();

};

