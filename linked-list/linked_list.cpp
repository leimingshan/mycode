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
	LinkNode *p1 = NULL;
	LinkNode *p2 = head;
	LinkNode *p;
	if(head == NULL)
		return NULL;
	while(p2 != NULL)
	{
		p = p2->next;
		p2->next = p1;
		
		p1 = p2;
		p2 = p;
	}
	return p1;
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