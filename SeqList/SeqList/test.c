#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"


void  Test1()
{
	SeqList  s;
	SeqListInit(&s);
	SeqListPushBack(&s,1);
	SeqListPushBack(&s,2);
	SeqListPushBack(&s,3);
	SeqListPushBack(&s,4);
	
	SeqListPopBack(&s);
	SeqListPrintf(&s);

	SeqListPushFront(&s,0);
	SeqListPrintf(&s);

	SeqListPopFront(&s);
	SeqListPrintf(&s);
	
	printf("%d", SeqListFind(&s,2));
	SeqListErase(&s, 1);
	SeqListPrintf(&s);
	SeqListInsert(&s, 1, 20);
	SeqListPrintf(&s);
}
void Test2()
{
	SeqList  s;
	SeqListInit(&s);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 5);
	SeqListPushBack(&s, 7);
	SeqListPushBack(&s, 8);
	SeqListPushBack(&s, 0);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 4);

	SeqListBubbleSort(&s);
	SeqListPrintf(&s);
	
	printf("%d\n", SeqListBinaryFind(&s,0));
	printf("%d\n", SeqListBinaryFind(&s,1));
	printf("%d\n", SeqListBinaryFind(&s, 2));
	printf("%d\n", SeqListBinaryFind(&s, 3));
	printf("%d\n", SeqListBinaryFind(&s, 4));
	printf("%d\n", SeqListBinaryFind(&s, 5));
	printf("%d\n", SeqListBinaryFind(&s, 6));
	printf("%d\n", SeqListBinaryFind(&s, 7));
	printf("%d\n", SeqListBinaryFind(&s, 8));
	printf("%d\n", SeqListBinaryFind(&s, 9));

}
void Test3()
{
	SeqList  s;
	SeqListInit(&s);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 5);
	SeqListPushBack(&s, 7);
	SeqListPushBack(&s, 8);
	SeqListPushBack(&s, 0);
	SeqListPushBack(&s, 3);
	SeqListPushBack(&s, 4);

	SeqListBubbleSort(&s);
	SeqListPrintf(&s);
}



int main()
{
	Test3();
	return 0;

}