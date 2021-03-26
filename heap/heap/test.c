#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"

void Testheap()
{
	int a[10] = { 27 };
	Heap hp;
	HeapCreate(&hp, a, 1);
	//HeapPrint(&hp);

	//HeapPop(&hp);
	HeapPush(&hp, -1);
	HeapPush(&hp, -3);
	HeapPush(&hp, 5);
	HeapPush(&hp, 90);
	//HeapPush(&hp, -100);
	HeapPrint(&hp);

	//printf("%d \n", HeapTop(&hp));
	//
	////°Ë´ÎÉ¾³ý
	//HeapPop(&hp);
	//HeapPop(&hp);
	//HeapPop(&hp);
	//HeapPop(&hp);
	//HeapPop(&hp);
	//HeapPop(&hp);
	//HeapPop(&hp);
	//HeapPop(&hp);

	//printf("%d \n",HeapEmpty(&hp));
	//printf("%d \n", HeapSize(&hp));
	//HeapPop(&hp);
	//printf("%d \n", HeapEmpty(&hp));
	//printf("%d \n", HeapSize(&hp));

	//HeapDestory(&hp);

}

int main()
{
	Testheap();
	return 0;
}