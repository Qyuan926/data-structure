#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"

void Testheap()
{
	int a[10] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	Heap hp;
	HeapCreate(&hp, a, 10);
	//HeapPrint(&hp);

	//HeapPop(&hp);
	HeapPush(&hp, -1);
	
	HeapPrint(&hp);
	HeapPush(&hp, 90);
	HeapPrint(&hp);

	//printf("%d \n", HeapTop(&hp));
	//
	////�˴�ɾ��
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