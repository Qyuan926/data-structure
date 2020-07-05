#define _CRT_SECURE_NO_WARNINGS 1
#include<string>
#include"map.h"
#include"set.h"


void test_map()
{





	string strs[] = { "西瓜", "樱桃", "西瓜", "苹果", "西瓜", "西瓜", "西瓜", "苹果" };
	Map::map<string, int> countMap;
	for (auto& str : strs)
	{
		// 1、如果水果不在map中，则operator[]会插入pair<str, 0>, 返回映射对象(次数)的引用进行了++。
		// 2、如果水边在map中，则operator[]返回水果对应的映射对象(次数)的引用，对它++。
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
// //   m.insert("西瓜", 1);
//	//m.insert("西瓜", 3);
//	//m.insert("西瓜", 4);
//	//m.insert("西瓜", 7);
//	//m.insert("西瓜", 8);
//
//	m.insert(pair<string,int>("西瓜",1));
//	m.insert(pair<string, int>("苹果", 2));
//	m.insert(pair<string, int>("樱桃", 3));
//	m.insert(pair<string, int>("梨", 4));
//	m.insert(pair<string, int>("柠檬", 5));
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