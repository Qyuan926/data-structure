#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"vector.h"
using namespace std;

void Testconstruct()
{
	MyVector::vector<int> v(7, 1);
	for (auto e : v)
	{
		cout << e<<" ";
	}
	cout << endl;
	MyVector::vector<int> v1(v);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
	v1[0] = 7;
	MyVector::vector<int> v2=v1;
	for (auto e : v2)
	{
		cout << e << " ";
	}
	cout << endl;
}
void Testmodify()
{
	
	MyVector::vector<int> v(7, 1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.push_back(666);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.pop_back();
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	
	v.insert(v.begin() + 2, 7);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
	v.erase(v.begin() + 3);
	v.erase(v.begin() + 3);
	v.erase(v.begin() + 3);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}





int main()
{
	//Testconstruct();
	Testmodify();
	
	return 0;
}
