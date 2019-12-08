#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int  SLDataType;



typedef struct  SeqList
{
	SLDataType * _array;
	size_t _size;
	size_t _capcity;
}SeqList;




void SeqListInit(SeqList* ps);
void SeqListDestory(SeqList* ps);

void SeqListPrintf(SeqList* ps);

void CheckCapacity(SeqList* ps);

void SeqListPushBack(SeqList* ps, SLDataType x);
void SeqListPopBack(SeqList* ps);
void SeqListPushFront(SeqList* ps, SLDataType x);
void SeqListPopFront(SeqList* ps);

int SeqListFind(SeqList* ps, SLDataType x);
void SeqListInsert(SeqList* ps, size_t pos, SLDataType x);
void SeqListErase(SeqList* ps, size_t pos);
void SeqListRemove(SeqList* ps, SLDataType x);


void SeqListBubbleSort(SeqList* ps);
int SeqListBinaryFind(SeqList* ps, SLDataType x);