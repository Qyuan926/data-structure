#define _CRT_SECURE_NO_WARNINGS 1
#include"HashMap.h"
#include"HashSet.h"
#include<iostream>
#include<string>
#include<unordered_set>



void test_hashmap()
{
	//HashMap::unordered_map<int, int> um;
	//um.insert(std::make_pair(1, 1));
	//um.insert(std::make_pair(2, 1));
	//um.insert(std::make_pair(3, 1));
	//um.insert(std::make_pair(4, 1));
	//um.insert(std::make_pair(5, 1));
	//um.insert(std::make_pair(7, 1));
	
	HashMap::unordered_map<std::string, std::string> um1;
	um1.insert(std::make_pair("����","Qyuan"));
	um1["left"] = "ʣ��";
	HashMap::unordered_map<std::string,std::string>::iterator it = um1.begin();
	while (it != um1.end())
	{
		std::cout << (*it).first << " " << (*it).second << std::endl;
		++it;
	}
}

void test_set()
{
	HashSet::unordered_set<std::string > us;
	us.insert("����");
	us.insert("Qyuan");
	us.insert("����");
	us.insert("����");
	HashSet::unordered_set<std::string>::iterator it = us.begin();
	while (it != us.end())
	{
		std::cout << *it << std::endl;
		++it;
	}
}



int main()
{
	test_hashmap();
	std::cout << "����ʵ��" << std::endl;
	test_set();
	
	return 0;
}