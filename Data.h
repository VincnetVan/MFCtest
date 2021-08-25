#pragma once

#include <locale>
#include <afx.h>
#include <vector>
#include <map>

struct stuDict
{
	CString _class_name;
	std::vector<CString> _names;
};
typedef std::vector<stuDict*> Dicts;


class CData
{
public:
	CData();
	~CData();
	//��ȡ����
	void ReadFile();
	//���Һ���,�ڶ�����������ָ��B,C,D,E...�����
	int Find(char type, CString s, int& tIndex, int& sIndex);
	//ɾ������
	int Del(CString s, char type);
	//�޸ĺ���
	void Modify(CString s, char type);
	//���Ӻ���
	void Insert(CString s, char type);
	//��ȡȫ������
	std::vector<CString> GetAll(char type);
	//��ȡ�ļ�·��
	CString GetFilePath();
	//�����ļ�·��
	void SetFilePath(CString path);
private:
	//���ڽ�����indexת��Ϊ������,�����ں���ʹ��
	std::vector<CString>::iterator GetItr(int index);
	//��ѯ_names�������������ͬ���ַ�����λ�ã����򷵻�false
	int FindNamePos(CString s, int typePos);
	//��ѯ����ָ�루bcd����������е�����
	int FindTypePos(char type);
private:
	Dicts m_vDicts;							//�洢studictsָ���vector����
	bool isChanged;							//�����Ƿ��޸ĵı�־��Ӧ��ʵ����ʱ��Ϊfalse�����ڹ��캯���ĳ�ʼ���б��У�
	CString FilePath;						//�洢Ҫ�򿪵��ļ���·��

};