#define _CRT_SECURE_NO_WARNINGS 1
#include"List.h"

ListNode* BuyListNode(LTDataType x)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode));
	newnode->_data = x;
	newnode->_next=NULL;
	newnode->_prev = NULL;
	return newnode;
}

ListNode* ListCreate()
{
	ListNode*  head = (ListNode*)malloc(sizeof(ListNode));
	head->_next = head;
	head->_prev = head;
	return head;
}
// ˫����������
void ListDestory(ListNode* plist)
{
	free(plist);
	plist = NULL;
}
// ˫�������ӡ
void ListPrint(ListNode* plist)
{
	ListNode* cur = plist->_next;
	while (cur != plist)
	{
		printf("%d->", cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}
// ˫������β��
void ListPushBack(ListNode* plist, LTDataType x)
{
	ListNode* newnode = BuyListNode(x);
	ListNode* tail = plist->_prev;
	tail->_next = newnode;
	newnode->_prev = tail;

	plist->_prev = newnode;
	newnode->_data = x;
}
// ˫������βɾ
void ListPopBack(ListNode* plist)
{
	//assert(plist->_prev == plist);
	ListNode* tail = plist->_prev;
	
	ListNode* newtail = tail->_prev;
	newtail->_next=plist;
	plist->_prev=newtail;
	free(tail);
	tail = NULL;
}
// ˫������ͷ��
void ListPushFront(ListNode* plist, LTDataType x)
{
	/*ListNode* newnode = BuyListNode(x);
	ListNode* headNext = plist->_next;
	plist->_next=newnode;
	newnode->_prev = plist;

	newnode->_next = headNext;
	headNext->_prev = newnode;*/
	ListInsert(plist->_next, x);

}
// ˫������ͷɾ
void ListPopFront(ListNode* plist)
{
	ListNode* headNext = plist->_next;

	plist->_next = headNext->_next;
	headNext->_next->_prev = plist;
		free(headNext);
		headNext = NULL;

}
// ˫���������
ListNode* ListFind(ListNode* plist, LTDataType x)
{
	ListNode* cur = plist->_next;
	while (cur != plist)
	{
		if (cur->_data == x)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

// ˫��������pos��ǰ����в���
void ListInsert(ListNode* pos, LTDataType x)
{
	ListNode* pos_prev = pos->_prev;
	ListNode* newnode = BuyListNode(x);
	pos_prev->_next = newnode;
	newnode->_prev = pos_prev;

	newnode->_next = pos;
	pos->_prev=newnode;
}
// ˫������ɾ��posλ�õĽڵ�
void ListErase(ListNode* pos)
{
	ListNode* prev = pos->_prev;
	ListNode* next = pos->_next;

	prev->_next = next;
	next->_prev = prev;
	free(pos);
	pos = NULL;

}