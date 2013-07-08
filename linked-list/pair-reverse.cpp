//链表相邻元素翻转，如a->b->c->d->e->f-g，翻转后变为：b->a->d->c->f->e->g

#include <iostream>
#include "linked_list.h"

using namespace std;

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

void print_list(LinkNode *head)
{
	LinkNode *temp = head;
	for(temp = head; temp != NULL; temp = temp->next)
		cout << temp->value <<' ';
	cout << endl;
	return;
}

int main()
{
	//build linked_list
	LinkNode *head = new LinkNode;
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
	
	//print linked_list
	print_list(head);
    
    LinkNode *newhead;
	newhead = inverse_pair(head);
	
	print_list(newhead);
	//destroy linked_list
	LinkNode *temp2;
	for(temp = newhead; temp != NULL; )
	{
		temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
	
	return 0;
}
