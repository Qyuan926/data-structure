#define _CRT_SECURE_NO_WARNINGS 1
#include<string>
#include"map.h"
#include"set.h"


void test_map()
{





	string strs[] = { "����", "ӣ��", "����", "ƻ��", "����", "����", "����", "ƻ��" };
	Map::map<string, int> countMap;
	for (auto& str : strs)
	{
		// 1�����ˮ������map�У���operator[]�����pair<str, 0>, ����ӳ�����(����)�����ý�����++��
		// 2�����ˮ����map�У���operator[]����ˮ����Ӧ��ӳ�����(����)�����ã�����++��
		countMap[str]++;
	}
	for (auto kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}

	
}

//void test_map()
//{
//	Map::map<string, int> m;
// //   m.insert("����", 1);
//	//m.insert("����", 3);
//	//m.insert("����", 4);
//	//m.insert("����", 7);
//	//m.insert("����", 8);
//
//	m.insert(pair<string,int>("����",1));
//	m.insert(pair<string, int>("ƻ��", 2));
//	m.insert(pair<string, int>("ӣ��", 3));
//	m.insert(pair<string, int>("��", 4));
//	m.insert(pair<string, int>("����", 5));
//
//
//	Map::map<string, int>::iterator it = m.begin();
//	while (it != m.end())
//	{
//		cout << it->first << ":" << it->second << endl;
//		++it;
//	}
//	cout << endl;
//
//	
//}
void test_set()
{
	Set::set<int> s;
	s.insert(3);
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(5);

	Set::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

int main()
{
	test_map();
	test_set();
	return 0;
}