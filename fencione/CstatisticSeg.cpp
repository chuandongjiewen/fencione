#include "StdAfx.h"
#include "CstatisticSeg.h"


CstatisticSeg::CstatisticSeg(void)
{

}

CstatisticSeg::~CstatisticSeg(void)
{
}

void CstatisticSeg::init()
{
	this->cutTime=0;
	this->sourceWordMap.clear();
	this->leftWordMap.clear();
	this->resultVect.clear();
}

CString CstatisticSeg::doCut(CString sentence)
{
	long begin = GetTickCount();
	int position = 0;
	int sumLen = sentence.GetLength();
	while(position < sumLen)
	{
		CString word = sentence.Mid(position, 1);
		map<CString, DictItem>::iterator it;
		while((it = dictionary.find(word)) != dictionary.end())
		{
			WordItem item;
			item.start = position;
			item.end = position + word.GetLength();
			item.word = it->first;
			item.frequency = it->second.frequency;
			if (position == 0)
			{
				item.multiFrequency = 1;
			}else{
				//item.multiFrequency = calMultiFrequency(&item);
				calMultiFrequency(&item);
			}

			//将该词加入左邻词map, 结束位置作为Key
			int end = item.end;
			map<int, vector<WordItem>>::iterator itLeft = leftWordMap.find(end);
			vector<WordItem> leftWord;
			if (itLeft != leftWordMap.end())
			{
				leftWord = itLeft->second;
			}
			leftWord.push_back(item);
			leftWordMap[item.end] = leftWord;
			
			CString key;
			key.Format(_T("%d")+it->first, item.start);
			sourceWordMap[key] = item;//加入到分词map
			
			if (sumLen == position + item.word.GetLength())
			{
				lastWord = item;//记录最后一个词
				break;
			}
			word = sentence.Mid(position, word.GetLength() + 1);
		}

		position ++;
		
	}
	CString result = this->output();
	int end = GetTickCount();

	this->cutTime = end - begin;

	return result;
}

CString CstatisticSeg::output()
{
	WordItem tmpWord = lastWord;
	CString result = tmpWord.word;
	map<CString, WordItem>::iterator it;
	CString key = _T("");
	key.Format(_T("%d")+tmpWord.word, tmpWord.start);
	resultVect.push_back(tmpWord.word);//push最后一个单词
	while((it = sourceWordMap.find(key)) != sourceWordMap.end())
	{
		tmpWord = it->second;
		resultVect.push_back(tmpWord.leftWord);
		result =  tmpWord.leftWord + _T("/ ") +result;
		int leftWordStart = tmpWord.start - tmpWord.leftWord.GetLength();
		if (leftWordStart == 0)
		{
			break;
		}
		key.Format(_T("%d")+tmpWord.leftWord, leftWordStart);
	}

	//将结果reverse以正序
	std::reverse(resultVect.begin(), resultVect.end());

	return result;
}

double CstatisticSeg::calMultiFrequency(WordItem *wordItem)
{
	map<int, vector<WordItem>>::iterator itLeft = leftWordMap.find(wordItem->start);
	vector<WordItem> leftWord;
	if (itLeft != leftWordMap.end())
	{
		leftWord = itLeft->second;
	}
	
	std::sort(leftWord.begin(), leftWord.end(), WordItem());
	WordItem leftItem = leftWord.at(0);
	wordItem->bestLeftWord = &leftItem;
	wordItem->leftWord = leftItem.word;
	
	double multi = wordItem->frequency * leftItem.multiFrequency;
	wordItem->multiFrequency = multi;
	return multi;
}

//bool CstatisticSeg::compareWord(const WordItem &item1, const WordItem &item2)
//{
//	return item1.multiFrequency < item2.multiFrequency;
//}

void CstatisticSeg::loadDict(CString dictPath)
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
		if (len>=3)
		{
			CString word = arr[0];
			CString numStr = arr[1];
			CString frequenceStr = arr[2].Left(arr[2].GetLength() - 1);
			

			int num = _ttoi(numStr);
			double frequence = _tstof(frequenceStr);

			DictItem dict;
			dict.num = num;
			dict.frequency = frequence;
			dictionary[word] = dict;
		}
		i++;
		delete[] tmp;
	}

	int end = GetTickCount();

	dictTime = end - begin;

	infile.close();
}
