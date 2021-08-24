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
	//读取函数
	void ReadFile();
	//查找函数,第二个参数用来指定B,C,D,E...等类别
	int Find(char type, CString s, int& tIndex, int& sIndex);
	//删除函数
	int Del(CString s, char type);
	//修改函数
	void Modify(CString s, char type);
	//增加函数
	void Insert(CString s, char type);
	//获取全部数据
	std::vector<CString> GetAll(char type);
	//获取文件路径
	CString GetFilePath();
	//设置文件路径
	void SetFilePath(CString path);
private:
	//用于将数字index转换为迭代器,供类内函数使用
	std::vector<CString>::iterator GetItr(int index);
	//查询_names容器中与参数相同的字符串的位置，无则返回false
	int FindNamePos(CString s, int typePos);
	//查询类型指针（bcd类别）在容器中的索引
	int FindTypePos(char type);
private:
	Dicts m_vDicts;							//存储studicts指针的vector容器
	bool isChanged;							//数据是否被修改的标志，应在实例化时置为false（即在构造函数的初始化列表中）
	CString FilePath;						//存储要打开的文件的路径

};