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


class CHMMSeg
{

private:
	map<CString, POS*> initialization;//��ʼ����,keyΪ���Ա�ע
	int sumOfInit; //��ʼ���ܺ�

	map<CString, POS*> transition;//ת�Ƹ��� keyΪ���Ա�ע
	map<CString, int> sumLineTran;// ת�Ƹ���ÿһ�е�sum

	map<CString, POS*> emission;//������� keyΪ���Ա�ע
	map<CString, int> sumLineEmission; //�������ÿһ�е�sum

	vector<CString> posVect; //���д��Ա�ע�ļ��� �����д��Ա�ע
	vector<CString> wordsVect;//���дʵļ��� �����еĵ���

public:
	CHMMSeg(void);
	~CHMMSeg(void);
	
	void init();
	//---------------��ʼ���ʵļ���----------------------------------------------
	void processInitial(CString dictPath);
	void calInitial(int m, double p);
	void writeInitial(CString path);

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


