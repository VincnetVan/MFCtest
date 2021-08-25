#include <stdafx.h>
#include "Data.h"


CData::CData() : isChanged(false), FilePath(_T("C:\\Users\\zhangs-ak\\Desktop\\ziku.txt"))
{

}

CData::~CData()
{
	//free the memory of the struct whose pointers pointed to
	for (std::vector<stuDict*>::iterator itr = m_vDicts.begin();  itr != m_vDicts.end(); ++itr)
	{
		if (*itr != NULL)
		{
			delete *itr;
			*itr = NULL;
		}
		m_vDicts.clear();
	}
}

void CData::ReadFile()
{
	std::map<CString, int> kind;
	CString B(_T("#BEGIN_[B]"));
	CString C(_T("#BEGIN_[C]"));
	CString D(_T("#BEGIN_[D]"));
	kind[B] = 1;
	kind[C] = 2;
	kind[D] = 3;

	//读取文件
	CStdioFile file;
	CFileException exp;

	char *old_locale = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");
	if (file.Open(FilePath, CFile::typeText | CFile::modeRead, &exp) == FALSE)
	{
		CString sMsg;
		exp.GetErrorMessage(sMsg.GetBuffer(1024),1024);
		sMsg.ReleaseBuffer();
		return;
	}

	CString sValue;
	while (file.ReadString(sValue))
	{
		switch(kind[sValue])
		{
		case 1:
			{	//读入B类型数据
				file.ReadString(sValue);
				stuDict* tmpDict = new stuDict;
				tmpDict->_class_name = 'B';
				m_vDicts.push_back(tmpDict);
				while (sValue != _T("#END_[B]"))
				{
					tmpDict->_names.push_back(sValue);
					file.ReadString(sValue);
				}
				//读入完毕，退出switch，由第一层while再次读入下一行数据，接着循环
			}
			break;
		case 2:
			{	//读入C类型数据
				file.ReadString(sValue);
				stuDict* tmpDict = new stuDict;
				tmpDict->_class_name = 'C';
				m_vDicts.push_back(tmpDict);
				while (sValue != _T("#END_[C]"))
				{
					tmpDict->_names.push_back(sValue);
					file.ReadString(sValue);
				}
				//读入完毕，退出switch，由第一层while再次读入下一行数据，接着循环
			}
			break;
		case 3:
			{	//读入D类型数据
				file.ReadString(sValue);
				stuDict* tmpDict = new stuDict;
				tmpDict->_class_name = 'D';
				m_vDicts.push_back(tmpDict);
				while (sValue != _T("#END_[D]"))
				{
					tmpDict->_names.push_back(sValue);
					file.ReadString(sValue);
				}
				//读入完毕，退出switch，由第一层while再次读入下一行数据，接着循环
			}
			break;
		default:
			break;
		}
	}

	//还原语言区域的设置和还原区域设定
	setlocale(LC_CTYPE, old_locale);
	free(old_locale);

	file.Close();
}

//如果找不到对应名称，则返回错误宏,如果找到了，则参数tIndex中存储类型索引，sIndex中存储名称容器中的索引
int CData::Find(char type, CString s, int& tIndex, int& sIndex)
{
	//tIndex接收type（bcd大类）对应的一级索引
	tIndex = FindTypePos(type);
	//sIndex接收具体名称s所对应的一级索引内部的二级索引
	sIndex = FindNamePos(s, tIndex);

	if (tIndex == FALSE || sIndex == FALSE)
	{
		return FALSE;
	}

	return 1;
}

int CData::Del(CString s, char type)
{
	int tPos = 0;
	int sPos = 0;
	
	if (Find(type, s, tPos, sPos))
	{
		m_vDicts[tPos]->_names.erase(m_vDicts[tPos]->_names.begin() + sPos);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

void CData::Modify(CString s, char type)
{
	int tPos = 0;
	int sPos = 0;
	if (Find(type, s, tPos, sPos))
	{
		m_vDicts[tPos]->_names[sPos] = s;
		return;
	}	
}

void CData::Insert(CString s, char type)
{
	int tPos = FindTypePos(type);
	if (tPos != FALSE)
	{
		m_vDicts[tPos]->_names.push_back(s);
	}
	else
	{
		return;
	}
}

std::vector<CString> CData::GetAll(char type)
{
	int pos = FindTypePos(type);
	if (pos == FALSE)
	{
		exit(0);
	}
	return m_vDicts[pos]->_names;
}

CString CData::GetFilePath()
{
	return FilePath;
}

void CData::SetFilePath(CString path)
{
	FilePath = path;
}

std::vector<CString>::iterator CData::GetItr(int index)
{
	std::vector<CString>::iterator itr;
	return itr;
}

int CData::FindNamePos(CString s, int typePos)
{
	int i = 0;
	while ((m_vDicts[typePos]->_names[i]) != s)
	{
		++i;
	}
	if(i >= m_vDicts[typePos]->_names.size())
	{
		return FALSE;
	}

	return i;
}

int CData::FindTypePos(char type)
{
	int i = 0;
	while (m_vDicts[i]->_class_name != type)
	{
		i++;
	}

	if (i >= m_vDicts.size())
	{
		return FALSE;
	}

	return i;
}

