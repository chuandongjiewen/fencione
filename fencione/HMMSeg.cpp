#include "StdAfx.h"
#include "HMMSeg.h"


CHMMSeg::CHMMSeg(void)
{
}


CHMMSeg::~CHMMSeg(void)
{
}


void CHMMSeg::init()
{
	transition.clear();
}

void CHMMSeg::processTransition(CString dictPath)
{
	int begin = GetTickCount();

	ifstream infile;
	infile.open(dictPath, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}

	CSplitStr splitLine;
	splitLine.SetSplitFlag(_T("  "));
	splitLine.SetSequenceAsOne(TRUE);

	bool isopen = infile.is_open();
	int id = 0;

	while(!infile.eof())
	{
		char* tmp = new char[40960];
		infile.getline(tmp,40960);

		CString str(tmp); 
		splitLine.SetData(str);
		CStringArray lineArr;
		splitLine.GetSplitStrArray(lineArr);
		int len = lineArr.GetCount();
		if (len == 0)
		{
			continue;
		}
		CSplitStr splitWord;
		splitWord.SetSplitFlag(_T("/"));
		splitWord.SetSequenceAsOne(TRUE);
		for (int i=1; i<len-1; i++)
		{
			CStringArray iWordArr;
			CStringArray jWordArr;
			splitWord.SetData(lineArr[i]);
			splitWord.GetSplitStrArray(iWordArr);

			splitWord.SetData(lineArr[i+1]);
			splitWord.GetSplitStrArray(jWordArr);
			if (iWordArr.GetCount() >= 2 && jWordArr.GetCount() >=2)
			{
				CString iPos = iWordArr[1];
				CString jPos = jWordArr[1];
				createTransitionPos(iPos, jPos);
			}

		}

		CString index;
		index.Format(_T("-------%d %s \n"),id++, str);
		OutputDebugStringW(index);
		delete[] tmp;
	}

	int end = GetTickCount();

	int time  = end - begin;

	infile.close();
}


POS* CHMMSeg::createTransitionPos(CString iPos, CString jPos)
{
	map<CString, ListPOS*>::iterator itIPos = transition.find(iPos);
	ListPOS *listpos;
	map<CString, POS*> posMap;
	POS *pos;
	if (itIPos == transition.end())
	{
		listpos = new ListPOS();
		posMap = listpos->posMap;
		listpos->sum = 1;

		pos = new POS();
		pos->iPos = iPos;
		pos->jPos = jPos;
		pos->num = 1;
		//pos->frequency = ((double)pos->num/listpos->sum);
		posMap[jPos] = pos;
		listpos->posMap = posMap;
		transition[iPos] = listpos;
	}else{
		listpos = itIPos->second;
		posMap = listpos->posMap;
		map<CString, POS*>::iterator itJPos = posMap.find(jPos);
		
		if (itJPos == posMap.end())
		{
			listpos->sum += 1;

			pos = new POS();
			pos->iPos = iPos;
			pos->jPos = jPos;
			pos->num = 1;
			//pos->frequency = ((double)pos->num/listpos->sum);
			posMap[jPos] = pos;
			
			listpos->posMap = posMap;
		}else{
			listpos->sum += 1;

			pos = itJPos->second;
			pos->num += 1;
			//pos->frequency = ((double)pos->num/listpos->sum);
		}
	}
	return pos;
}


void CHMMSeg::calTransition(int m, double p)
{
	vector<CString> keyVect;
	for(map<CString, ListPOS*>::iterator itIPos = transition.begin(); itIPos != transition.end(); itIPos ++)
	{
		keyVect.push_back(itIPos->first);
	}

	for (vector<CString>::iterator i = keyVect.begin(); i != keyVect.end(); i++)
	{
		map<CString, ListPOS*>::iterator itIPos = transition.find(*i);
		ListPOS *listPos = itIPos->second;
		int sum = listPos->sum;
		map<CString, POS*> posMap = listPos->posMap;
		for (vector<CString>::iterator j = keyVect.begin(); j != keyVect.end(); j++)
		{
			map<CString, POS*>::iterator itJPos = posMap.find(*j);
			POS *pos;
			if (itJPos != posMap.end())
			{
				pos = itJPos->second;
				pos->frequency = ((double)(pos->num + m*p)) / (sum + m);
			}else{
				pos = new POS();
				pos->iPos = *i;
				pos->jPos = *j;
				pos->num = 0;
				pos->frequency = ((double) 0 + m*p) / (sum + m);
				posMap[*j] = pos;
			}
			
		}
		listPos->posMap = posMap;
	}


}


//将发射概率写入文件
void CHMMSeg::writeTransition(CString path)
{
	CStdioFile fout;
	BOOL isopen = fout.Open(path, CFile::modeReadWrite|CFile::modeCreate);
	if (!isopen)
	{
		return;
	}
	fout.SeekToBegin();

	map<CString, ListPOS*>::iterator itIPos;
	for(itIPos = transition.begin(); itIPos != transition.end(); itIPos ++)
	{
		ListPOS *listPos = itIPos->second;
		OutputDebugStringW(itIPos->first + _T("--first-"));
		map<CString, POS*> posMap = listPos->posMap;
		map<CString, POS*>::iterator itJPos;
		for (itJPos = posMap.begin(); itJPos != posMap.end(); itJPos++)
		{
			POS* pos = itJPos->second;
			CString tmp;
			tmp.Format(_T("%d,%f\r\n"),pos->num,pos->frequency);
			fout.WriteString(pos->iPos+_T(",")+pos->jPos+_T(",")+tmp);
			
		}
	}

	fout.Flush();
	fout.Close();
}

void CHMMSeg::readTransition(CString path)
{
	int begin = GetTickCount();

	ifstream infile;
	infile.open(path, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}

	CSplitStr splitLine;
	splitLine.SetSplitFlag(_T("-"));
	splitLine.SetSequenceAsOne(TRUE);

	bool isopen = infile.is_open();
	int id = 0;

	while(!infile.eof())
	{
		char* tmp = new char[1024];
		infile.getline(tmp,1024);

		CString str(tmp); 
		splitLine.SetData(str);
		CStringArray lineArr;
		splitLine.GetSplitStrArray(lineArr);
		int len = lineArr.GetCount();
		if (len < 4)
		{
			continue;
		}
		
		CString ipos = lineArr[0];
		CString jpos = lineArr[1];
		int num = _ttoi(lineArr[2]);
		double frequency = _tstof(lineArr[3]);

		

		CString index;
		index.Format(_T("-------%d %s \n"),id++, str);
		OutputDebugStringW(index);
		delete[] tmp;
	}

	int end = GetTickCount();

	int time  = end - begin;
	
	infile.close();
}


void CHMMSeg::processEmission(CString dictPath)
{
	int begin = GetTickCount();

	ifstream infile;
	infile.open(dictPath, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}

	CSplitStr splitLine;
	splitLine.SetSplitFlag(_T("  "));
	splitLine.SetSequenceAsOne(TRUE);

	bool isopen = infile.is_open();
	int id = 0;

	while(!infile.eof())
	{
		char* tmp = new char[40960];
		infile.getline(tmp,40960);

		CString str(tmp); 
		splitLine.SetData(str);
		CStringArray lineArr;
		splitLine.GetSplitStrArray(lineArr);
		int len = lineArr.GetCount();
		if (len == 0)
		{
			continue;
		}
		CSplitStr splitWord;
		splitWord.SetSplitFlag(_T("/"));
		splitWord.SetSequenceAsOne(TRUE);
		for (int i=1; i<len; i++)//从1开始，去除日期
		{
			CStringArray iWordArr;

			splitWord.SetData(lineArr[i]);
			splitWord.GetSplitStrArray(iWordArr);
			if (iWordArr.GetCount() >= 2)
			{
				CString jPos = iWordArr[0];//词
				CString iPos = iWordArr[1];//词性
				createEmissionPos(iPos, jPos);
			}

		}

		CString index;
		index.Format(_T("-------%d %s \n"),id++, str);
		OutputDebugStringW(index);
		delete[] tmp;
	}

	int end = GetTickCount();

	int time  = end - begin;

	infile.close();
}


POS* CHMMSeg::createEmissionPos(CString iPos, CString jPos)
{
	map<CString, ListPOS*>::iterator itIPos = emission.find(iPos);
	ListPOS *listpos;
	map<CString, POS*> posMap;
	POS *pos;
	if (itIPos == emission.end())
	{
		listpos = new ListPOS();
		posMap = listpos->posMap;
		listpos->sum = 1;

		pos = new POS();
		pos->iPos = iPos;
		pos->jPos = jPos;
		pos->num = 1;
		//pos->frequency = ((double)pos->num/listpos->sum);
		posMap[jPos] = pos;
		listpos->posMap = posMap;
		emission[iPos] = listpos;

		wordsVect.push_back(jPos);//将该词加入到词典向量中
	}else{
		listpos = itIPos->second;
		posMap = listpos->posMap;
		map<CString, POS*>::iterator itJPos = posMap.find(jPos);

		if (itJPos == posMap.end())
		{
			listpos->sum += 1;

			pos = new POS();
			pos->iPos = iPos;
			pos->jPos = jPos;
			pos->num = 1;
			posMap[jPos] = pos;

			listpos->posMap = posMap;
			wordsVect.push_back(jPos);//将该词加入到词典向量中
		}else{
			listpos->sum += 1;

			pos = itJPos->second;
			pos->num += 1;
		}
	}
	return pos;
}

void CHMMSeg::calEmission(int m, double p)
{
	vector<CString> keyVect;//词性集合
	for(map<CString, ListPOS*>::iterator itIPos = emission.begin(); itIPos != emission.end(); itIPos ++)
	{
		keyVect.push_back(itIPos->first);
	}

	for (vector<CString>::iterator i = keyVect.begin(); i != keyVect.end(); i++)
	{
		map<CString,ListPOS*>::iterator itIPos = emission.find(*i);
		ListPOS *listPos = itIPos->second;
		int sum = listPos->sum; //如：标记为词性V的词的总和
		map<CString, POS*> posMap = listPos->posMap; //词的map
		for (vector<CString>::iterator j = wordsVect.begin(); j != wordsVect.end(); j++)
		{
			map<CString, POS*>::iterator itJPos = posMap.find(*j);
			POS *pos;
			if (itJPos != posMap.end())
			{
				pos = itJPos->second;
				pos->frequency = ((double)(pos->num + m*p)) / (sum + m);
			}else{
				pos = new POS();
				pos->iPos = *i;
				pos->jPos = *j;
				pos->num = 0;
				pos->frequency = ((double) 0 + m*p) / (sum + m);
				posMap[*j] = pos;
			}
		}
		listPos->posMap = posMap;
	}
	
}


void CHMMSeg::writeEmission(CString path)
{
	CStdioFile fout;
	BOOL isopen = fout.Open(path, CFile::modeReadWrite|CFile::modeCreate);
	if (!isopen)
	{
		return;
	}
	fout.SeekToBegin();
	char* old_locale = _strdup(setlocale(LC_CTYPE,NULL));
	setlocale( LC_CTYPE, "chs" );//设定

	map<CString, ListPOS*>::iterator itIPos;
	for(itIPos = emission.begin(); itIPos != emission.end(); itIPos ++)
	{
		ListPOS *listPos = itIPos->second;
		OutputDebugStringW(itIPos->first + _T("--first-"));
		map<CString, POS*> posMap = listPos->posMap;
		map<CString, POS*>::iterator itJPos;
		for (itJPos = posMap.begin(); itJPos != posMap.end(); itJPos++)
		{
			POS* pos = itJPos->second;
			CString tmp;
			tmp.Format(_T("%d,%f\r\n"),pos->num,pos->frequency);
			fout.WriteString(pos->iPos+_T(",")+pos->jPos+_T(",")+tmp);

		}
	}

	setlocale( LC_CTYPE, old_locale );
	free(old_locale);//还原区域设定

	fout.Flush();
	fout.Close();
}