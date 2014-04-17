#include "StdAfx.h"
#include "Hmm.h"


CHmm::CHmm(void)
{
	m = 10;
	p = 0.000001;
	maxLastVet = NULL;
}


CHmm::~CHmm(void)
{
}

void CHmm::reset()
{
	wordsVect.clear();
	maxLastVet = NULL;
	lastVetVector.clear();
	resultMap.clear();
}

void CHmm::setEstimate(int m, double p)
{
	this->m = m;
	this->p = p;
}

void CHmm::setWords(vector<CString> data)
{
	this->reset();
	this->wordsVect = data;
	this->init();
}

void CHmm::loadInit(CString path)
{
	int begin = GetTickCount();

	ifstream infile;
	infile.open(path, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}

	char *tmp = new char[100];

	CSplitStr splitStr;

	splitStr.SetSplitFlag(_T(","));
	splitStr.SetSequenceAsOne(true);

	CString key;
	while(!infile.eof()){
		infile.getline(tmp, 100);
		CString tmpStr(tmp);
		CStringArray tmpArr;

		splitStr.SetData(tmpStr);
		splitStr.GetSplitStrArray(tmpArr);

		int len = tmpArr.GetCount();
		if (len < 3) continue;

		CString ipos = tmpArr[0];
		int num = _ttoi(tmpArr[1]);
		double frequency = _tstof(tmpArr[2]);

		POS *pos = new POS();
		pos->iPos = ipos;
		pos->num = num;
		pos->frequency = frequency;

		key = ipos;
		initMap[key] = pos;
	}

	delete[] tmp;
	int end = GetTickCount();
	int time = end - begin;
	infile.close();
}

void CHmm::loadEmission(CString path)
{
	int begin = GetTickCount();

	ifstream infile;
	infile.open(path, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}
	
	char *tmp = new char[100];
	
	CSplitStr splitStr;

	splitStr.SetSplitFlag(_T(","));
	splitStr.SetSequenceAsOne(true);
	
	CString key;
	while(!infile.eof()){
		infile.getline(tmp, 100);
		CString tmpStr(tmp);
		CStringArray tmpArr;
		
		splitStr.SetData(tmpStr);
		splitStr.GetSplitStrArray(tmpArr);

		int len = tmpArr.GetCount();
		if (len < 4) continue;

		CString ipos = tmpArr[0];
		CString jpos = tmpArr[1];
		int num = _ttoi(tmpArr[2]);
		double frequency = _tstof(tmpArr[3]);

		POS *pos = new POS();
		pos->iPos = ipos;
		pos->jPos = jpos;
		pos->num = num;
		pos->frequency = frequency;

		key = ipos + _T("-") + jpos;
		emissionMap[key] = pos;
		
		map<CString, int>::iterator iterSum = sumOfEm.find(ipos);
		if (iterSum == sumOfEm.end())
		{
			sumOfEm[ipos] = 1;
		}else{
			int sum = sumOfEm[ipos];
			sumOfEm[ipos] = sum + 1;
		}
	}

	delete[] tmp;
	int end = GetTickCount();
	int time = end - begin;
	infile.close();
}


void CHmm::loadTransition(CString path)
{
	int begin = GetTickCount();

	ifstream infile;
	infile.open(path, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}

	char *tmp = new char[100];

	CSplitStr splitStr;

	splitStr.SetSplitFlag(_T(","));
	splitStr.SetSequenceAsOne(true);

	CString key;
	while(!infile.eof()){
		infile.getline(tmp, 100);
		CString tmpStr(tmp);
		CStringArray tmpArr;

		splitStr.SetData(tmpStr);
		splitStr.GetSplitStrArray(tmpArr);

		int len = tmpArr.GetCount();
		if (len < 4) continue;

		CString ipos = tmpArr[0];
		CString jpos = tmpArr[1];
		int num = _ttoi(tmpArr[2]);
		double frequency = _tstof(tmpArr[3]);

		POS *pos = new POS();
		pos->iPos = ipos;
		pos->jPos = jpos;
		pos->num = num;
		pos->frequency = frequency;

		key = ipos + _T("-") + jpos;
		transitionMap[key] = pos;

		//将iPos加入到集合中
		vector<CString>::iterator iterPos = std::find(posVect.begin(), posVect.end(), ipos);
		if (iterPos == posVect.end())
		{
			posVect.push_back(ipos);
		}

		map<CString, int>::iterator iterSum = sumOfTran.find(ipos);
		if (iterSum == sumOfTran.end())
		{
			sumOfTran[ipos] = 1;
		}else{
			int sum = sumOfTran[ipos];
			sumOfTran[ipos] = sum + 1;
		}
	}

	delete[] tmp;
	int end = GetTickCount();
	int time = end - begin;
	infile.close();
}

void CHmm::init()
{
	/*wordsVect.push_back(_T("结合"));
	wordsVect.push_back(_T("成"));
	wordsVect.push_back(_T("分子"));
	wordsVect.push_back(_T("时"));*/
	for (vector<CString>::iterator iterPos = posVect.begin(); iterPos != posVect.end(); iterPos++)
	{
		CString word = wordsVect.at(0);
		CString ipos = *iterPos;
		CString key = _T("0-") + word +_T("-") + ipos;
		CString emKey = ipos +_T("-") + word;
		double initFrequency = (initMap[ipos] == NULL) ? 0.000001 : initMap[ipos]->frequency; //初始概率

		int sum = (sumOfEm[ipos] >= 0) ? sumOfEm[ipos] : 0;
		POS *pos = emissionMap[emKey];
		double emFrequency = 0; //发射概率
		if (pos == NULL)
		{
			emFrequency = ((double) 0 + p*m) / (m + sum);
		}else{
			emFrequency = ((double) pos->num + p*m) / (m + sum);
		}
		Vet *vet = new Vet();
		vet->id = 0;
		vet->pos = ipos;
		vet->word = word;
		vet->frequency = initFrequency * emFrequency;
		vet->preVet  =NULL;
		resultMap[key] = vet;
		
	}
	
}

void CHmm::calculate()
{
	for (int i=1; i<wordsVect.size(); i++)
	{
		CString curWord = wordsVect.at(i);
		CString preWord = wordsVect.at(i-1);
		int len = posVect.size();
		for (int j=0; j<posVect.size(); j++)//控制当前时刻
		{
			CString curPos = posVect.at(j);
			double maxLastFreqency = 0; //记录最大的v特比概率
			Vet *maxPreVet = NULL;//记录前驱最大的维特比结点
			//-------------求前驱概率乘以转移概率的最大值--------------------
			for (int k=0; k<posVect.size(); k++) //控制前一个时刻
			{
				CString prePos = posVect.at(k);
				CString tranKey = prePos + _T("-") + curPos;
				POS *a = transitionMap[tranKey];
				int sumTran = (sumOfTran[prePos] >= 0) ? sumOfEm[curPos] : 0;
				double tmpFrequency = 0;
				if (a == NULL)//数据平滑
				{	
					tmpFrequency = ((double) 0 + p*m) / (m + sumTran);
				}else{
					tmpFrequency = ((double) a->frequency + p*m) / (m + sumTran);
				}
				
				CString prekey;//Vj-1的概率
				prekey.Format(_T("%d"), i-1);
				prekey = prekey + _T("-") + preWord + _T("-") + prePos;
				Vet *preVet = resultMap[prekey];

				//将前一项的维特比概率乘以路径的转移概率
				tmpFrequency = tmpFrequency*(preVet->frequency);
				if (tmpFrequency > maxLastFreqency)
				{
					maxLastFreqency = tmpFrequency;
					maxPreVet = preVet;
				}
			}

			//---------求发射概率--------------
			int sumEm = (sumOfEm[curPos] >= 0) ? sumOfEm[curPos] : 0;
			CString emKey = curPos + _T("-") + curWord;
			POS *pos = emissionMap[emKey];
			double emFrequency = 0; //发射概率
			if (pos == NULL)
			{
				emFrequency = ((double) 0 + p*m) / (m + sumEm);
			}else{
				emFrequency = ((double) pos->num + p*m) / (m + sumEm);
			}

			//-----------求当前时刻的维特比概率-----------------------
			CString curKey;
			curKey.Format(_T("%d"), i);
			curKey = curKey + _T("-") + curWord + _T("-") + curPos;
			Vet *curVet = new Vet();
			curVet->id = i;
			curVet->pos = curPos;
			curVet->word = curWord;
			curVet->preVet = maxPreVet;
			curVet->frequency = maxLastFreqency*emFrequency;//前项乘以发射概率
			resultMap[curKey] = curVet;

			if (i == wordsVect.size() - 1)
			{
				if (maxLastVet == NULL || curVet->frequency > maxLastVet->frequency)
				{
					maxLastVet = curVet;
				}
				lastVetVector.push_back(curVet);
			}
		}
	}
}

CString CHmm::output()
{
	CString resultStr = _T("");
	Vet *tmpVet = maxLastVet;
	while(tmpVet != NULL)
	{
		resultStr = tmpVet->word + _T("/") + tmpVet->pos  + _T("  ") + resultStr ;
		tmpVet = tmpVet->preVet;
	}
	return resultStr;
}