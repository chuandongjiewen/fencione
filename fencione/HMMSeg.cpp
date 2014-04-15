#include "StdAfx.h"
#include "HMMSeg.h"


CHMMSeg::CHMMSeg(void)
{
	sumOfInit = 0;
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

		/*CString index;
		index.Format(_T("-------%d %s \n"),id++, str);
		OutputDebugStringW(index);*/
		delete[] tmp;
	}

	int end = GetTickCount();

	int time  = end - begin;

	infile.close();
}


POS* CHMMSeg::createTransitionPos(CString iPos, CString jPos)
{
	CString key = iPos + _T("-") + jPos;
	map<CString, POS*>::iterator iterIPos = transition.find(key);
	POS* pos;
	if (iterIPos == transition.end())
	{
		pos = new POS();
		pos->iPos = iPos;
		pos->jPos = jPos;
		pos->num = 1;
		transition[key] = pos;
	}else{
		pos = iterIPos->second;
		pos->num += 1;
	}

	//更新每一行的总和
	map<CString, int>::iterator iterSumLine = sumLineTran.find(iPos);
	int sumOfLine;
	if (iterSumLine != sumLineTran.end())
	{
		sumOfLine = iterSumLine->second;
		sumOfLine += 1;
	}else{
		sumOfLine = 1;
		posVect.push_back(iPos);
	}
	sumLineTran[iPos] = sumOfLine;

	return pos;
}


void CHMMSeg::calTransition(int m, double p)
{
	for(vector<CString>::iterator i = posVect.begin(); i != posVect.end(); i++)
	{
		map<CString, int>::iterator iterSum = sumLineTran.find(*i);
		int sum = iterSum->second; //转移概率每一行的总和
		for (vector<CString>::iterator j = posVect.begin(); j != posVect.end(); j++)
		{
			CString key = *i + _T("-") + *j;
			map<CString, POS*>::iterator iterPos = transition.find(key);
			POS *pos;
			if (iterPos != transition.end())
			{
				pos = iterPos->second;
				pos->frequency = ((double)(pos->num + m*p)) / (sum + m);
			}else{
				pos =  new POS();
				pos->iPos = *i;
				pos->jPos = *j;
				pos->num = 0;
				pos->frequency = ((double)(0 + m*p)) / (sum + m);
			}
			transition[key] = pos;
		}
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

	map<CString, POS*>::iterator iterIPos;
	for(iterIPos = transition.begin(); iterIPos != transition.end(); iterIPos ++)
	{
		POS *pos = iterIPos->second;
		CString tmp;
		tmp.Format(_T("%d,%f\r\n"),pos->num, pos->frequency);
		fout.WriteString(pos->iPos+_T(",")+pos->jPos+_T(",")+tmp);
		//OutputDebugStringW(iterIPos->first + _T(",") + tmp);		
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

		

		/*CString index;
		index.Format(_T("-------%d %s \n"),id++, str);
		OutputDebugStringW(index);*/
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

		/*CString index;
		index.Format(_T("-------%d %s \n"),id++, str);
		OutputDebugStringW(index);*/
		delete[] tmp;
	}

	int end = GetTickCount();

	int time  = end - begin;

	infile.close();
}


POS* CHMMSeg::createEmissionPos(CString iPos, CString jPos)
{
	CString key = iPos + _T("-") + jPos;
	map<CString, POS*>::iterator iterIPos = emission.find(iPos);
	POS *pos;
	if (iterIPos == emission.end())
	{
		pos = new POS();
		pos->iPos = iPos;
		pos->jPos = jPos;
		pos->num = 1;
		emission[key] = pos;
	}else{
		pos = iterIPos->second;
		pos->num += 1;
	}

	map<CString, int>::iterator iterLine = sumLineEmission.find(iPos);
	int sum = 0;
	if (iterLine == sumLineEmission.end())
	{
		posVect.push_back(iPos);
		sum = 1;
	}else{
		sum = iterLine->second + 1;
	}
	sumLineEmission[iPos] = sum;

	vector<CString>::iterator iterWords = find(wordsVect.begin(), wordsVect.end(), jPos);
	if (iterWords == wordsVect.end())
	{
		wordsVect.push_back(jPos);
	}
	return pos;
}

void CHMMSeg::calEmission(int m, double p)
{
	//vector<CString> keyVect;//词性集合
	//for(map<CString, POS*>::iterator itIPos = emission.begin(); itIPos != emission.end(); itIPos ++)
	//{
	//	keyVect.push_back(itIPos->first);
	//}

	for (vector<CString>::iterator i = posVect.begin(); i != posVect.end(); i++)
	{
		
		map<CString,int>::iterator iterSumEm = sumLineEmission.find(*i);
		int sum = iterSumEm->second; //如：标记为词性V的词的总和
		for (vector<CString>::iterator j = wordsVect.begin(); j != wordsVect.end(); j++)
		{
			CString key = *i + _T("-") + *j;
			map<CString, POS*>::iterator iterEmission = emission.find(key);
			POS *pos;
			if (iterEmission != emission.end())
			{
				pos = iterEmission->second;
				pos->frequency = ((double)(pos->num + m*p)) / (sum + m);
			}else{
				pos = new POS();
				pos->iPos = *i;
				pos->jPos = *j;
				pos->num = 0;
				pos->frequency = ((double)(0 + m*p)) / (sum + m);
			}
			emission[key] = pos;
		}
		
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

	map<CString, POS*>::iterator iterIPos;
	for(iterIPos = emission.begin(); iterIPos != emission.end(); iterIPos ++)
	{
		POS *pos = iterIPos->second;
		CString tmp;
		tmp.Format(_T("%d,%f\r\n"),pos->num, pos->frequency);
		fout.WriteString(pos->iPos+_T(",")+pos->jPos+_T(",")+tmp);
		//OutputDebugStringW(iterIPos->first + _T(",") + tmp);	
	}

	setlocale( LC_CTYPE, old_locale );
	free(old_locale);//还原区域设定

	fout.Flush();
	fout.Close();
}

void CHMMSeg::processInitial(CString dictPath)
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
	splitLine.SetSplitFlag(_T("。"));//将每段话按照句号分开
	splitLine.SetSequenceAsOne(TRUE);

	bool isopen = infile.is_open();
	int id = 0;

	while(!infile.eof())
	{
		char* tmp = new char[40960];
		infile.getline(tmp,40960);

		CString str(tmp); 
		str = str.Mid(23,str.GetLength());//去除每段开头的日期
		splitLine.SetData(str);
		CStringArray lineArr;
		splitLine.GetSplitStrArray(lineArr);
		int len = lineArr.GetCount();
		if (len == 0)
		{
			continue;
		}
		CSplitStr splitWord;
		splitWord.SetSequenceAsOne(TRUE);
		for (int i=0; i<len; i++)//将每一句按照双空格分开
		{
			CStringArray iWordArr;
			CString lineStr = lineArr[i];
			if (i != 0 && lineStr.GetLength() > 4)
			{
				lineStr = lineStr.Mid(4,lineStr.GetLength());		
			}
			splitWord.SetSplitFlag(_T("  "));//将每一句按照双空格分开
			splitWord.SetData(lineStr);
			splitWord.GetSplitStrArray(iWordArr);
			
			CStringArray finalWordArr;
			CString tmpStr;
			tmpStr = iWordArr[0];
			
			splitWord.SetSplitFlag(_T("/")); //将每个词按照/分开
			splitWord.SetData(tmpStr);
			splitWord.GetSplitStrArray(finalWordArr);

			int count = finalWordArr.GetCount();
			if ( count >=2)
			{
				CString word = finalWordArr[0];
				CString posStr = finalWordArr[1];

				sumOfInit ++;
				POS *pos;
				map<CString, POS*>::iterator iterInit = initialization.find(posStr);
				if (iterInit == initialization.end())
				{
					pos = new POS();
					pos->iPos = word;
					pos->jPos = posStr;
					pos->num = 1;	
					initialization[posStr] = pos;
				}else{
					pos = iterInit->second;
					pos->num += 1;
				}
			}
		}

		delete[] tmp;
	}

	int end = GetTickCount();

	int time  = end - begin;

	infile.close();
}

void CHMMSeg::calInitial(int m, double p)
{
	for (map<CString, POS*>::iterator iterInit = initialization.begin(); iterInit != initialization.end(); iterInit++)
	{
		POS *pos = iterInit->second;
		pos->frequency = ((double)(pos->num + m*p)) / ( sumOfInit+ m);
	}
}

void CHMMSeg::writeInitial(CString path)
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

	for (map<CString, POS*>::iterator iterInit = initialization.begin(); iterInit != initialization.end(); iterInit++)
	{
		POS *pos = iterInit->second;
		CString tmp;
		tmp.Format(_T("%d,%f\r\n"),pos->num, pos->frequency);
		fout.WriteString(pos->iPos+_T(",")+pos->jPos+_T(",")+tmp);
		//OutputDebugStringW(iterInit->first + _T(",") + tmp);	
	}

	setlocale( LC_CTYPE, old_locale );
	free(old_locale);//还原区域设定

	fout.Flush();
	fout.Close();
}