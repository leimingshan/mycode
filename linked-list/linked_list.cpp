#include <iostream>
#include <stack>
#include "linked_list.h"

using namespace std;

ListNode *BuildList(ListNode *&head)
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

int DestroyList(ListNode *head)
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

void PrintList(ListNode *head)
{
	ListNode *temp = head;
	for(temp = head; temp != NULL; temp = temp->next)
		cout << temp->value <<' ';
	cout << endl;
	return;
}

unsigned int GetListLength(ListNode *head)
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

ListNode *ReverseList(ListNode *head)
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

ListNode *ReverseListRecursive(ListNode *head)
{
	if(head == NULL || head->next == NULL)
		return head;
	ListNode *p = head->next;
	ListNode *h = ReverseListRecursive(p);
	p->next = head;
	head->next = NULL;
	return h;
}

//链表相邻元素翻转，如a->b->c->d->e->f-g，翻转后变为：b->a->d->c->f->e->g
ListNode *InversePair(ListNode *head)
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
ListNode *RGetKthNode(ListNode *head, unsigned int k) // 函数名前面的r代表反向
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

ListNode *GetMiddleNode(ListNode *head)
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

//从尾到头打印单链表
//使用栈
void RPrintList(ListNode *head)
{
	if (head == NULL)
		return;
	stack<ListNode *> s;
	ListNode *node = head;
	while (node != NULL) {
		s.push(node);
		node = node->next;
	}
	while (!s.empty()) {
		cout << s.top()->value << ' ';
		s.pop();
	}
	return;
}
//使用递归
void RPrintListRecursive(ListNode *head)
{
	if (head == NULL)
		return;
	RPrintListRecursive(head->next);
	cout << head->value << ' ';
}

//判断一个单链表中是否有环
bool HasCircle(ListNode *head)
{
	ListNode * fast = head; // 快指针每次前进两步
	ListNode * slow = head; // 慢指针每次前进一步
	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if(slow == fast) // 相遇，存在环
			return true;
	}
	return false;
}

//已知一个单链表中存在环，求进入环中的第一个节点
ListNode* GetFirstNodeInCircle(ListNode * head)
{
	if(head == NULL || head->next == NULL)
		return NULL;

	ListNode * fast = head;
	ListNode * slow = head;
	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast)
			break;
	}
	if(fast == NULL || fast->next == NULL)
		return NULL;

	// 将环中的此节点作为假设的尾节点，将它变成两个单链表相交问题
	ListNode * assumed_tail = slow; 
	ListNode * head1 = head;
	ListNode * head2 = assumed_tail->next;

	int len1 = 1;
	ListNode * node1 = head1;
	while(node1 != assumed_tail)
	{
		node1 = node1->next;
		len1++;
	}
	
	int len2 = 1;
	ListNode * node2 = head2;
	while(node2 != assumed_tail)
	{
		node2 = node2->next;
		len2++;
	}

	node1 = head1;
	node2 = head2;
	// 先对齐两个链表的当前结点，使之到尾节点的距离相等
	if(len1 > len2)
	{
		int k = len1 - len2;
		while(k--)
			node1 = node1->next;
	}
	else
	{
		int k = len2 - len1;
		while(k--)
			node2 = node2->next;
	}
	while(node1 != node2)
	{
		node1 = node1->next;
		node2 = node2->next;
	}
    return node1;
}