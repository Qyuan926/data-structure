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
// 双向链表销毁
void ListDestory(ListNode* plist)
{
	free(plist);
	plist = NULL;
}
// 双向链表打印
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
// 双向链表尾插
void ListPushBack(ListNode* plist, LTDataType x)
{
	ListNode* newnode = BuyListNode(x);
	ListNode* tail = plist->_prev;
	tail->_next = newnode;
	newnode->_prev = tail;

	plist->_prev = newnode;
	newnode->_data = x;
}
// 双向链表尾删
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
// 双向链表头插
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
// 双向链表头删
void ListPopFront(ListNode* plist)
{
	ListNode* headNext = plist->_next;

	plist->_next = headNext->_next;
	headNext->_next->_prev = plist;
		free(headNext);
		headNext = NULL;

}
// 双向链表查找
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

// 双向链表在pos的前面进行插入
void ListInsert(ListNode* pos, LTDataType x)
{
	ListNode* pos_prev = pos->_prev;
	ListNode* newnode = BuyListNode(x);
	pos_prev->_next = newnode;
	newnode->_prev = pos_prev;

	newnode->_next = pos;
	pos->_prev=newnode;
}
// 双向链表删除pos位置的节点
void ListErase(ListNode* pos)
{
	ListNode* prev = pos->_prev;
	ListNode* next = pos->_next;

	prev->_next = next;
	next->_prev = prev;
	free(pos);
	pos = NULL;

}