#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"



void TestList()
{
	ListNode* list = ListCreate();



	ListPushBack(list, 1);
	ListPushBack(list, 2);
	ListPushBack(list, 3);
	ListPushBack(list, 4);
	ListPushBack(list, 5);
	ListPopBack(list);
	ListPopBack(list);
	ListPopBack(list);
	

	ListPushFront(list, 1);
	ListPushFront(list, 2);
	ListPushFront(list, 3);
	ListPushFront(list, 4);
	ListPushFront(list, 5);
	//ListPopFront(list);
	//ListPopFront(list);
	//ListPopFront(list);
	

	ListPrint(list);
	ListNode* ret1=ListFind(list,5);
	ListNode* ret2 = ListFind(list,7);
	if (ret1 != NULL)
	{
		printf("%d\n", ret1->_data);
	}
	if (ret2 != NULL)
	{
		printf("%d\n", ret2->_data);
	}
	else
	{
		printf("ret2");
	}
	ListDestory(list);

}







int main()
{
	TestList();
	return 0;
}