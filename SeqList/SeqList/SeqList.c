#define _CRT_SECURE_NO_WARNINGS 1
#include"SeqList.h"
void SeqListInit(SeqList* ps)
{
	assert(ps);
	ps->_array = NULL;
	ps->_size = 0;
	ps->_capcity = 0;
}
void SeqListDestory(SeqList* ps)
{
	assert(ps);
	free(ps->_array);
	ps->_array = NULL;
	ps->_capcity = 0;
	ps->_size = 0;
}
void SeqListPrintf(SeqList* ps)
{
	assert(ps);
	for (size_t i = 0; i< ps->_size; ++i)
	{
		printf("%d  ", ps->_array[i]);
	}
	printf("\n");
}
void CheckCapacity(SeqList* ps)
{
	assert(ps);
	if (ps->_size >= ps->_capcity)
	{
		size_t newcapcity = ps->_capcity==0 ? 4 : ps->_capcity * 2;
		//防止capcity为0 出现错误
		ps->_array = realloc(ps->_array,newcapcity*sizeof( SLDataType));
		ps->_capcity = newcapcity;
	}

}
void SeqListPushBack(SeqList* ps, SLDataType x)
{
	assert(ps);
	//数组空间是否足够  Whether the array space is sufficient
	CheckCapacity(ps);
	ps->_array[ps->_size++] = x;

}
void SeqListPopBack(SeqList* ps)
{
	assert(ps);
	ps->_size--;
}
void SeqListPushFront(SeqList* ps, SLDataType x)
{

	assert(ps);
	CheckCapacity(ps);
	size_t end = ps->_size ;
	for (; end > 0; --end)
	{
		ps->_array[end] = ps->_array[end-1];


	}
	ps->_array[0] = x;
	ps->_size++;
}
void SeqListPopFront(SeqList* ps)
{
	assert(ps);
	for (size_t i = 0; i < ps->_size - 1;++i)
	{
		ps->_array[i] = ps->_array[i + 1];
	}
	ps->_size--;
}
//查数 返回该数的位置；
int SeqListFind(SeqList* ps, SLDataType x)
{
	for (size_t i = 0; i < ps->_size; ++i)
	{
		if (ps->_array[i] == x)
		{
			return i;
		}
	}
	return -1;
}
//在pos位置插入x值。
void SeqListInsert(SeqList* ps, size_t pos, SLDataType x)
{
	assert(ps&&pos<ps->_size);//防止顺序表之外插入，越界
	CheckCapacity(ps);
	for (size_t i = ps->_size - 1; i >= pos + 1; i--)
	{
		ps->_array[i + 1] = ps->_array[i];
	}
	ps->_size++;
	ps->_array[pos] = x;
}
//删除某个位置的点
void SeqListErase(SeqList* ps, size_t pos)
{
	assert(ps&&pos<ps->_size);//防止越界访问

		for (size_t i = pos; i < ps->_size-1; i++)
		{
			ps->_array[i] = ps->_array[i + 1];
		}
	
	ps->_size--;
}
//找到x  删除该点
void SeqListRemove(SeqList* ps, SLDataType x)
{
	assert(ps);
	int i=SeqListFind(ps, x);
	if (i >= 0)
	{
		SeqListErase(ps, i);
	}
}
void SeqListBubbleSort(SeqList* ps)
{
	assert(ps);
	int change = 1;
	for (size_t i = 1; i < ps->_size - 1 && change; ++i)
	{
		change = 0;
		for(size_t j = 0; j < ps->_size - i; ++j)
		{
			if (ps->_array[j]>ps->_array[j + 1])
			{
				SLDataType tmp = ps->_array[j];
				ps->_array[j] = ps->_array[j + 1];
				ps->_array[j + 1] = tmp;
				change = 1;
			}
		}
	}
}
//int SeqListBinaryFind(SeqList* ps, SLDataType x)
//{
//	size_t left = 0, right = ps->_size - 1;//[]
//	size_t mid = 0;
//	while (left <= right)//*left<right 会死循环
//	{mid= (left + right) / 2;
//		if (ps->_array[mid]==x)
//		{
//			return mid;
//		}
//		if (ps->_array[mid] < x)
//		{
//			left = mid + 1;//*
//		}
//		else
//			right = mid - 1;//*
//	}
//	return -1;
//}
int SeqListBinaryFind(SeqList* ps, SLDataType x)
{
	size_t left = 0, right = ps->_size;//[)
	size_t mid = 0;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (ps->_array[mid] == x)
		{
			return mid;
		}
		if (ps->_array[mid] < x)
		{
			left = mid + 1;
		}
		else
			right = mid;
	}
	return -1;
}