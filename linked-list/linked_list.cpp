#include <iostream>
#include "linked_list.h"

using namespace std;

unsigned int get_list_length(LinkNode *head)
{
    if(head == NULL)
        return 0;
    unsigned int len = 0;
	LinkNode *temp = head;
	while(temp != NULL)
	{
		len++;
		temp = temp->next;
	}
    return len;
}

LinkNode *reverse_list(LinkNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;

	LinkNode *newhead = NULL;
	LinkNode *current = head;
	LinkNode *p;
	
	while(current != NULL)
	{
		p = current->next;
		current->next = newhead;
		
		newhead = current;
		current = p;
	}
	return newhead;
}

LinkNode *reverse_list_recursive(LinkNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;
	LinkNode *p = head->next;
	LinkNode *h = reverse_list_recursive(p);
	p->next = head;
	head->next = NULL;
	return h;
}

//查找单链表中倒数第K个结点
LinkNode *r_get_kth_node(LinkNode *head, unsigned int k) // 函数名前面的r代表反向
{
	//使用两个指针，保持两个指针的距离差是k-1
	if (head == NULL || k == 0)
		return NULL;

	LinkNode *pAhead = head;
	LinkNode *pBehind = head;

	while (k > 1 && pAhead != NULL) {
		pAhead = pAhead->next;
		k--;
	}
	if (k > 1 || pAhead == NULL) // 结点个数小于k，返回NULL  
		return NULL;
	while (pAhead->next != NULL) {
		pAhead = pAhead->next;
		pBehind = pBehind->next;
	}
	return pBehind;
}

//链表相邻元素翻转，如a->b->c->d->e->f-g，翻转后变为：b->a->d->c->f->e->g
LinkNode *inverse_pair(LinkNode *head)
{
	if (head == NULL || head->next == NULL)
		return head;
	LinkNode *pre = head;
	LinkNode *curr = head->next;
	LinkNode *next = curr->next;
    LinkNode *newhead = head->next;

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

LinkNode *build_list(LinkNode *&head)
{
	LinkNode *temp = head;
	int i;
	for(i = 1; i < 12; i++)
	{
		temp->value = i;
		temp->next = new LinkNode;
		temp = temp->next;
	}
	temp->value = i;
	temp->next = NULL;
	return head;
}

int destroy_list(LinkNode *head)
{
	LinkNode *p;
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

void print_list(LinkNode *head)
{
	LinkNode *temp = head;
	for(temp = head; temp != NULL; temp = temp->next)
		cout << temp->value <<' ';
	cout << endl;
	return;
}
