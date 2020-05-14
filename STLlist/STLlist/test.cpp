#define _CRT_SECURE_NO_WARNINGS 1
#include"STLlist.h"
#include<iostream>
using namespace std;



void test_list1()
{
	List::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	cout << "lt:";
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	List::list<int> lt1(lt);
	cout << "lt1:";
	for (auto e : lt1)
	{
		cout  << e << " ";
	}
	cout << endl;

	List::list<int> lt2;
	lt2.push_back(7);
	lt2.push_back(8);
	lt2.push_back(9);
	cout << "lt2:";
	for (auto e : lt2)
	{
		cout  << e << " ";
	}
	cout << endl;
	lt2.swap(lt1);
	cout << "lt1和lt2链表交换后" << endl;
	cout << "lt1:";
	for (auto e : lt1)
	{
		cout  << e << " ";
	}
	cout << endl;
	cout << "lt2:";
	for (auto e : lt2)
	{
		cout  << e << " ";
	}
	cout << endl;



}
void test_list2()
{
	List::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	cout << "lt:";
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	lt.pop_back();
	cout << "lt popback :";
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	lt.push_front(0);
	lt.push_front(-1);
	cout << "lt pushfront :";
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
	lt.pop_front();
	cout << "lt popfront :";
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

}
void test_listiterator()
{
	List::list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	List::list<int> ::iterator  begin = lt.begin();
	for (; begin != lt.end();++begin)
	{
		cout << *begin << " ";
	}
	cout << endl;

}






int main()
{
	//test_list1();
	//test_list2();
	test_listiterator();
	return 0;
}