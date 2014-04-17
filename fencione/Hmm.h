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
	int id; //��ǰ�ʵ�id
	double frequency; //�ۼƸ���
	CString word; //�ʵ�����
	CString pos; //���Ա�ע
	Vet *preVet; //ǰ�����
};

class CHmm
{

public:
	double m; //m���Ƶ�ֵ Ĭ��10
	double p; //m���Ƶĸ��� Ĭ��0.5

public:

	vector<CString> posVect; // ���д��Ա�ע�ļ���
	vector<CString> wordsVect; //���д��ֵĴʵļ���

	map<CString, POS*> emissionMap;
	map<CString, POS*> transitionMap;
	map<CString, POS*> initMap;

	map<CString, int> sumOfEm; //ÿһ�з�����ʵĺ�
	map<CString, int> sumOfTran;//ÿһ��ת�Ƹ��ʵĺ�

	//�洢����·�ߵ� key: id,word,pos 
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
	void setEstimate(int m, double p);//����m���Ƶ�����ƽ��
	void setWords(vector<CString> data);
	CString output();

private: 
	void reset();

};

