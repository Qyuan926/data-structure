#define _CRT_SECURE_NO_WARNINGS 1
#include"AVLtree.h"
#include<iostream>
using namespace std;


void TestAVLTree()
{

	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLtree<int, int> t;
	for (auto e : a)
	{
		t.insert(make_pair(e, e));
	}

	

	t.IsBanlance();
}



int main()
{
	TestAVLTree();
	return 0;
}