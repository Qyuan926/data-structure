#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"
void HeapPrint(Heap* hp)
{
	assert(hp);
	for (int i = 0; i < hp->_size; ++i)
	{
		printf("%d ", hp->_a[i]);
	}
	printf("\n");
}
void Swap(HPDataType* x1, HPDataType* x2)
{
	HPDataType tmp = *x1;
	*x1 = *x2;
	*x2 = tmp;
}
void ADJustDown(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = 2 * parent + 1;
	while (child <=n)
	{
		if (child+1<n&&a[child + 1] < a[child])
		{
			++child;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}

}
// 堆的构建
void HeapCreate(Heap* hp, HPDataType* a, int n)
{
	assert(hp&&a);
	hp->_a = (HPDataType*)malloc(sizeof(HPDataType)*n);
	if (hp->_a == NULL)
	{
		printf("空间不足");
		return;
	}
	else{
		memcpy(hp->_a, a, sizeof(HPDataType)*n);
		hp->_capacity = n;
		hp->_size = n;
	}
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		ADJustDown(hp->_a, hp->_size, i);
	}

}
//建小堆
void ADJustUp(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = 2 * parent + 1;
	while (child < n)
	{
		if (child + 1 < n&&a[child + 1] < a[child])
		{
			++child;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}
	

// 堆的插入
void HeapPush(Heap* hp, HPDataType x)
{
	assert(hp);
	
	if (hp->_capacity == hp->_size)
	{
		hp->_capacity *= 2;
		 hp->_a = (HPDataType*)realloc(hp->_a, sizeof(HPDataType)*hp->_capacity);
		if (hp->_a == NULL)
		{
			printf("空间不足\n");
			return;
		}
	}
		
			
		hp->_a[hp->_size++] = x;

		
	
	for (int i = (hp->_size - 1 - 1) / 2; i >= 0; --i)
	{
		ADJustUp(hp->_a, hp->_size, i);
	}
}
// 堆的删除
void HeapPop(Heap* hp)
{
	assert(hp);
	Swap(&hp->_a[0], &hp->_a[hp->_size - 1]);
	--hp->_size;
	for (int i = (hp->_size - 1 - 1) / 2; i >= 0; --i)
	{
		ADJustDown(hp->_a, hp->_size, i);
	}
}
// 取堆顶的数据
HPDataType HeapTop(Heap* hp)
{
	assert(hp);
	if (HeapEmpty(hp))
	{
		printf("操作错误");
		return 0;
	}
	return hp->_a[0];
}
// 堆的数据个数
int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->_size;
}
// 堆的判空
int HeapEmpty(Heap* hp)
{
	assert(hp);
	return hp->_size == 0 ? 1 : 0;
}
// 堆的销毁
void HeapDestory(Heap* hp)
{
	assert(hp);
	free(hp->_a);
	hp->_a = NULL;
	hp->_capacity = hp->_size = 0;
}