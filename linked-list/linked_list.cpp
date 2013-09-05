#include <iostream>
#include "linked_list.h"

using namespace std;

ListNode *build_list(ListNode *&head)
{
	ListNode *temp = head;
	int i;
	for(i = 1; i < 12; i++)
	{
		temp->value = i;
		temp->next = new ListNode;
		temp = temp->next;
	}
	temp->value = i;
	temp->next = NULL;
	return head;
}

int destroy_list(ListNode *head)
{
	ListNode *p;
	if(head == NULL)
		return -1;
		
	while(head != NULL)
	{
		p = head->next;
		delete head;
		head = p;
	}
	return 0;
}

void print_list(ListNode *head)
{
	ListNode *temp = head;
	for(temp = head; temp != NULL; temp = temp->next)
		cout << temp->value <<' ';
	cout << endl;
	return;
}

unsigned int get_list_length(ListNode *head)
{
    if(head == NULL)
        return 0;
    unsigned int len = 0;
	ListNode *temp = head;
	while(temp != NULL)
	{
		len++;
		temp = temp->next;
	}
    return len;
}

ListNode *reverse_list(ListNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;

	ListNode *newhead = NULL;
	ListNode *current = head;
	ListNode *p;
	
	while(current != NULL)
	{
		p = current->next;
		current->next = newhead;
		
		newhead = current;
		current = p;
	}
	return newhead;
}

ListNode *reverse_list_recursive(ListNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;
	ListNode *p = head->next;
	ListNode *h = reverse_list_recursive(p);
	p->next = head;
	head->next = NULL;
	return h;
}

//链表相邻元素翻转，如a->b->c->d->e->f-g，翻转后变为：b->a->d->c->f->e->g
ListNode *inverse_pair(ListNode *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	ListNode *pre = head;
	ListNode *curr = head->next;
	ListNode *next = curr->next;
    ListNode *newhead = head->next;

	while(pre && pre->next)
	{
		curr = pre->next;
		next = curr->next;
		
		curr->next = pre;
        if(next != NULL)
		    pre->next = next->next;
        else
            pre->next = NULL;
        pre = next;
	}
	return newhead;
}

//查找单链表中倒数第K个结点
ListNode *r_get_kth_node(ListNode *head, unsigned int k) // 函数名前面的r代表反向
{
	//使用两个指针，保持两个指针的距离差是k-1
	if (head == NULL || k == 0) // 这里k的计数是从1开始的，若k为0或链表为空返回NULL
		return NULL;

	ListNode *pAhead = head;
	ListNode *pBehind = head;

	while (k > 1 && pAhead != NULL) { // 前面的指针先走到正向第k个结点
		pAhead = pAhead->next;
		k--;
	}
	if (k > 1 || pAhead == NULL) // 结点个数小于k，返回NULL  
		return NULL;
	while (pAhead->next != NULL) { // 前后两个指针一起向前走，直到前面的指针指向最后一个结点
		pAhead = pAhead->next;
		pBehind = pBehind->next;
	}
	return pBehind;
}

ListNode *get_middle_node(ListNode *head)
{
	if (head == NULL || head->next == NULL) // 链表为空或只有一个结点，返回头指针
		return head;

	ListNode *pAhead = head;
	ListNode *pBehind = head;

	while (pAhead != NULL && pAhead->next != NULL) {
		pAhead = pAhead->next->next;
		pBehind = pBehind->next;
	}

	return pBehind;
}