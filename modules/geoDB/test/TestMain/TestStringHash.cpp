


#include <string>
#include<map>
#include<unordered_map>

using namespace std;

#pragma once

#define MAXTABLELEN 1024    // Ĭ�Ϲ�ϣ�������С 
//////////////////////////////////////////////////////////////////////////  
// ��ϣ��������  
typedef struct  _HASHTABLE
{
	long nHashA;
	long nHashB;
	bool bExists;
}HASHTABLE, *PHASHTABLE;

class StringHash
{
public:
	StringHash(const long nTableLength = MAXTABLELEN);
	~StringHash(void);
private:
	unsigned long cryptTable[0x500];
	unsigned long m_tablelength;    // ��ϣ��������  
	HASHTABLE *m_HashIndexTable;
private:
	void InitCryptTable();                                               // �Թ�ϣ������Ԥ���� 
	unsigned long HashString(const string &lpszString, unsigned long dwHashType); // ��ȡ��ϣֵ      
public:
	bool Hash(string url);
	unsigned long Hashed(string url);    // ���url�Ƿ�hash��
};



StringHash::StringHash(const long nTableLength /*= MAXTABLELEN*/)
{
	InitCryptTable();
	m_tablelength = nTableLength;
	//��ʼ��hash��
	m_HashIndexTable = new HASHTABLE[nTableLength];
	for (int i = 0; i < nTableLength; i++)
	{
		m_HashIndexTable[i].nHashA = -1;
		m_HashIndexTable[i].nHashB = -1;
		m_HashIndexTable[i].bExists = false;
	}
}

StringHash::~StringHash(void)
{
	//�����ڴ�
	if (NULL != m_HashIndexTable)
	{
		delete[]m_HashIndexTable;
		m_HashIndexTable = NULL;
		m_tablelength = 0;
	}
}

/************************************************************************/
/*��������InitCryptTable
/*��  �ܣ��Թ�ϣ������Ԥ����
/*����ֵ����
/************************************************************************/
void StringHash::InitCryptTable()
{
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

	for (index1 = 0; index1 < 0x100; index1++)
	{
		for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp1 = (seed & 0xFFFF) << 0x10;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp2 = (seed & 0xFFFF);
			cryptTable[index2] = (temp1 | temp2);
		}
	}
}

/************************************************************************/
/*��������HashString
/*��  �ܣ���ȡ��ϣֵ
/*����ֵ������hashֵ
/************************************************************************/
unsigned long StringHash::HashString(const string& lpszString, unsigned long dwHashType)
{
	unsigned char *key = (unsigned char *)(const_cast<char*>(lpszString.c_str()));
	unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
	int ch;

	while (*key != 0)
	{
		ch = toupper(*key++);

		seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}
	return seed1;
}

/************************************************************************/
/*��������Hashed
/*��  �ܣ����һ���ַ����Ƿ�hash��
/*����ֵ��������ڣ�����λ�ã����򣬷���-1
/************************************************************************/
unsigned long StringHash::Hashed(string lpszString)

{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	//��ͬ���ַ�������hash������ײ�ļ������޽ӽ��ڲ�����
	unsigned long nHash = HashString(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString(lpszString, HASH_A);
	unsigned long nHashB = HashString(lpszString, HASH_B);
	unsigned long nHashStart = nHash % m_tablelength,
		nHashPos = nHashStart;

	while (m_HashIndexTable[nHashPos].bExists)
	{
		if (m_HashIndexTable[nHashPos].nHashA == nHashA && m_HashIndexTable[nHashPos].nHashB == nHashB)
			return nHashPos;
		else
			nHashPos = (nHashPos + 1) % m_tablelength;

		if (nHashPos == nHashStart)
			break;
	}

	return -1; //û���ҵ�  
}

/************************************************************************/
/*��������Hash
/*��  �ܣ�hashһ���ַ���
/*����ֵ���ɹ�������true��ʧ�ܣ�����false
/************************************************************************/
bool StringHash::Hash(string lpszString)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString(lpszString, HASH_A);
	unsigned long nHashB = HashString(lpszString, HASH_B);
	unsigned long nHashStart = nHash % m_tablelength,
		nHashPos = nHashStart;

	while (m_HashIndexTable[nHashPos].bExists)
	{
		nHashPos = (nHashPos + 1) % m_tablelength;
		if (nHashPos == nHashStart) //һ���ֻ�  
		{
			//hash����û�п����λ����,�޷����hash
			return false;
		}
	}
	m_HashIndexTable[nHashPos].bExists = true;
	m_HashIndexTable[nHashPos].nHashA = nHashA;
	m_HashIndexTable[nHashPos].nHashB = nHashB;

	return true;
}
//struct hash_func  //hash ����  
//{
//	size_t operator()(const char* str) const
//	{
//		unsigned long hash = 0;
//		size_t  len = strlen(str);
//
//		for (size_t i = 0; i < len; i++)
//		{
//			// @@ UNICODE: Does this function do the correct thing with wchar's?
//
//			const wchar_t temp = str[i];
//			hash = (hash << 4) + (temp * 13);
//
//			unsigned long g = hash & 0xf0000000;
//
//			if (g)
//			{
//				hash ^= (g >> 24);
//				hash ^= g;
//			}
//		}
//
//		return hash;
//	}
//};
//struct cmp_fun //�ȽϺ��� ==  
//{
//	bool operator()(const char* str1, const char* str2) const
//	{
//		return strcmp(str1, str2) == 0 ? true : false;
//	}
//};

//
//extern int run_main(int argc, char** argv)
//{
//
//
//
//	StringHash hash;
//	hash.Hash("guooujie");
//	unsigned long  l = hash.Hashed("guooujie");
//
//	std::hash<std::string> ss;
//	unsigned long  m = ss("guooujie");
//
//	std::unordered_map<string,int> jj;
//	jj.insert(std::unordered_map<string, int>::value_type("guooujie", 1234));
//	std::unordered_map<string, int>::iterator fiters;
//
//	string da("guooujie");
//	fiters = jj.find(da);
//
//
//
//	char * fff = (char*)malloc(strlen("guooujie")+1);
//	strcpy(fff, "guooujie");
//
//	std::unordered_map<char*, int, hash_func, cmp_fun> mmm;
//
//	mmm.insert(std::unordered_map<char*, int>::value_type(fff, 23456));
//	std::unordered_map<char*, int>::iterator iters;
//
//	char * gggg = (char*)malloc(strlen("guooujie") + 1);
//	strcpy(gggg, "guooujie");
//	iters = mmm.find(gggg);
//	
//	int i = iters->second;
//
//
//
//	return 0;
//}
#include "geoUtils.hh"
#include"geoStringMap.hh"

#pragma comment(lib,"geoUtils.lib")

extern int run_main(int argc, char** argv)
{

	GeoStringMap map;
	geoUInt32 d1 = 1;
	geoUInt32 d2 = 2;
	geoUInt32 d3 = 3;
	geoUInt32 d4 = 4;
	map.bind("tag1", d1);
	map.bind("tag2", d2);
	map.bind("tag3", d3);
	map.bind("tag4", d4);
	geoUInt32 f1;
	map.find("tag4", f1);

	map.unbind("tag3");
	geoUInt32 f2;
	map.find("tag3", f2);
	return 0;
}
int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}
