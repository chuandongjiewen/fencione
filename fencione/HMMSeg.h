#pragma once
#include <CString>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <afx.h>
#include "SplitStr.h"

using namespace std;

//ת�Ƹ��ʵ�ÿһ��
struct POS{
	CString iPos;//ǰ��
	CString jPos;//����
	int num;
	double frequency;
};

//ת�Ƹ��ʾ����ÿһ��
struct ListPOS{
	map<CString, POS*> posMap;//����Ϊkey�Ĵʵ��б�
	int sum;//���б�ע���ܺ�
};

class CHMMSeg
{

private:
	map<CString, ListPOS*> transition;//ת�Ƹ���
	map<CString, ListPOS*> emission;//�������
	vector<CString> wordsVect;

public:
	CHMMSeg(void);
	~CHMMSeg(void);
	
	void init();
	//---------------ת�Ƹ��ʵļ���----------------------------------------------
	void processTransition(CString dictPath);//��199801.txt����ȡԭʼ��Ϣ
	void calTransition(int m, double p);//����ת�Ƹ���, m �û�ָ������Ŀ 4�� pΪָ���ĸ���(0.5)
	void writeTransition(CString path);
	void readTransition(CString path);
	POS* createTransitionPos(CString iPos, CString jPos);//����һ�����Ա�ע��������������޸�Num+1


	//---------------������ʵļ���----------------------------------------------
	void processEmission(CString dictPath);
	POS* createEmissionPos(CString iPos, CString jPos);// ipos Ϊ���jPosΪ����
	void calEmission(int m, double p);
	void writeEmission(CString path);
};


