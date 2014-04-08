#include "StdAfx.h"
#include "Segment.h"



CSegment::CSegment(int maxLen)
{
	setMaxLen(maxLen);
}

void CSegment::init()
{
	//loadDict(_T("E:\\cpp\\fencione\\Debug\\dict.txt"));
	nResult.nullWords.clear();
	nResult.singleWords.clear();
	nResult.sumWords.clear();
	
	pResult.nullWords.clear();
	pResult.singleWords.clear();
	pResult.sumWords.clear();

}

void CSegment::setMaxLen(int maxLen)
{
	this->maxLen = maxLen;
}

CString CSegment::MMPositive(CString sentence)
{
	long begin = GetTickCount();
	//clock_t begin, end;
	//begin = clock();

	CString result = _T("");
	CString tempStr(sentence);

	int position = 0;
	int len = sentence.GetLength();
	maxLen = (maxLen > len) ? len : maxLen;
	int tempLen = maxLen;
	while(position <len)
	{
		/*tempLen = maxLen;
		while(tempLen>=1){
			CString substr = tempStr.Mid(position, tempLen);

			map<CString, CString>::iterator it =  dictionary.find(substr);
			if (it != dictionary.end())
			{
				result.Append(it->first +"/" + it->second + " ");
				break;
			}else{
				if (tempLen == 1)
				{
					result.Append(substr+"/wrong");
					break;
				}
				tempLen --;
			}
			
		}
		position += tempLen;*/

		bool isFound = true;
		if (len - position < maxLen)
		{
			tempLen = len - position;
		}
		CString substr = tempStr.Mid(position, tempLen);
		map<CString, CString>::iterator it;
		while((it = dictionary.find(substr)) == dictionary.end()){
			if (substr.GetLength() == 1)
			{
				isFound = false;
				break;
			}
			substr = substr.Left(substr.GetLength() - 1);
		}
		if (isFound)
		{
			result.Append(it->first +"/" + it->second + " ");
			if (substr.GetLength() == 1)
			{
				pResult.singleWords.push_back(substr);
			}
		}else{
			result.Append(substr+"/wrong" + " ");
			pResult.singleWords.push_back(substr);
			pResult.nullWords.push_back(substr);
		}
		pResult.sumWords.push_back(substr);

		position += substr.GetLength();

	}

	long end = GetTickCount();
	//end = clock();
	pTime = end - begin;

	return result;
}

CString CSegment::MMNegative(CString sentence)
{
	int begin  = GetTickCount();

	CString result = _T("");
	CString tempStr(sentence);

	int len = sentence.GetLength();
	int position = len-1;
	maxLen = (maxLen > len) ? len : maxLen;
	int tempLen = maxLen;
	while(position >= 0)
	{
		/*tempLen = maxLen;
		while(tempLen>=1){
			CString substr = tempStr.Mid(position + 1 - tempLen, tempLen);

			map<CString, CString>::iterator it =  dictionary.find(substr);
			if (it != dictionary.end())
			{
				result.Insert(0, _T(" ") + it->first +"/" + it->second);
				break;
			}else{
				if (tempLen == 1)
				{
					result.Insert(0, _T(" ") + substr+"/wrong");
					break;
				}
				tempLen --;
			}

		}
		position -= tempLen;*/

		bool isFound = true;
		if (position + 1 < maxLen)
		{
			tempLen = position + 1;
		}
		CString substr = tempStr.Mid(position + 1 - tempLen, tempLen);
		map<CString, CString>::iterator it;
		while((it = dictionary.find(substr)) == dictionary.end()){
			if (substr.GetLength() == 1)
			{
				isFound = false;
				break;
			}
			substr = substr.Right(substr.GetLength() - 1);

		}
		if (isFound)
		{
			result.Insert(0, _T(" ") + it->first +"/" + it->second);
			if (substr.GetLength() == 1)
			{
				nResult.singleWords.push_back(substr);
			}
		}else{
			result.Insert(0, _T(" ") + substr+"/wrong");
			nResult.singleWords.push_back(substr);
			nResult.nullWords.push_back(substr);
		}
		nResult.sumWords.push_back(substr);
		position = position - substr.GetLength();
	}

	int end = GetTickCount();
	nTime = end - begin;

	return result;
}

CString CSegment::MMDouble(CString sentence)
{
	CString pStr = MMPositive(sentence);
	CString nStr = MMNegative(sentence);
	int pNum = 0, nNum = 0;
	pNum = pResult.nullWords.size() + pResult.singleWords.size() + pResult.sumWords.size();
	nNum = nResult.nullWords.size() + nResult.singleWords.size() + nResult.sumWords.size();
	if (pNum >= nNum)
	{
		return pStr;
	}else{
		return nStr;
	}
}

void CSegment::loadDict(CString dictPath)
{
	long begin = GetTickCount();

	ifstream infile;
	infile.open(dictPath, ios::in);

	if (!infile)
	{
		infile.close();
		return;
	}

	CSplitStr split;
	split.SetSplitFlag(_T(","));
	split.SetSequenceAsOne(TRUE);

	bool isopen = infile.is_open();
	int i=0;

	while(!infile.eof())
	{
		char* tmp = new char[2048];
		//getline(infile, tmpStr, _T('\n'));
		infile.getline(tmp,2048);

		CString str(tmp);
		split.SetData(str);
		CStringArray arr;
		split.GetSplitStrArray(arr);
		int len = arr.GetCount();
		if (len>=2)
		{
			CString key = arr[0];
			CString value = arr[1];
			dictionary[key] = value;
		}
		i++;
		delete[] tmp;
	}
	
	int end = GetTickCount();

	dictTime = end - begin;

	infile.close();

}

int CSegment::ExtString(CString str, CStringArray &strArray)
{
	CString temp;
	int count = 0;
	strArray.RemoveAll();
	while(str.Find(_T(",")) != -1)
	{
		temp = str.Left(str.Find(_T(",")));
		str = str.Right(str.GetLength() - str.Find(_T(",")) - 2);
		strArray.Add(temp);
		count ++;
	}

	//最后一个字符串 
	if(str.GetLength()>0) 
	{ 
		strArray.Add(str);//提取出的字符加入动态数组 
		count++; 
	} 
	return count;
}


CSegment::~CSegment()
{
}
