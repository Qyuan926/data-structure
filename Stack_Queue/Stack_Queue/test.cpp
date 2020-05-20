#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack_Queue.h"
#include<iostream>
using namespace std;


void test_stack()
{
	stack::stack<int>  s;
	
	s.push(1);
	s.push(2);
	s.push(3);
	cout << s.size() << endl;
	while (!s.empty())
	{
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;

}
void test_queue()
{
	queue::queue<int>  q;

	q.push(1);
	q.push(2);
	q.push(3);
	cout << q.front() << endl;
	cout << q.back() << endl;
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}




int main()
{
	cout << "stack" << endl;
	test_stack();
	cout << "queue" << endl;
	test_queue();
	return 0;
}