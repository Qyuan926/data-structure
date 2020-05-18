#define _CRT_SECURE_NO_WARNINGS 1
#include"priority_que.h"
#include<iostream>
using namespace std;


int main()
{
	queue::priority_queue<int> q;
	q.push(6);
	q.push(20);
	q.push(7);
	q.push(100);
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}
	cout << endl;






	return 0;
}