#define _CRT_SECURE_NO_WARNINGS 1
#include"stack.h"
void Teststack()
{

	Stack p;
	StackInit(&p);
	StackPush(&p, 1);
	StackPush(&p, 2);
	StackPush(&p, 3);
	StackPush(&p, 4);
	StackPush(&p, 5);
	while (StackEmpty(&p) == 0)
	{
		printf("%d  ", StackTop(&p));
		StackPop(&p);
	}
	StackDestroy(&p);
}

int main()
{

	Teststack();
	return 0;
}