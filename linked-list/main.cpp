//Test for main functions of linked_list
#include <iostream>
#include "linked_list.h"

using namespace std;

int main()
{
	//build linked_list
	ListNode *head = new ListNode;
	head = BuildList(head);

	cout << "Original linked list:" << endl;
	PrintList(head);

	cout << "List length:" << endl << GetListLength(head) << endl;
	
	ListNode *reverse_head = ReverseList(head);
	cout << "Reversed linked list:" << endl;
	PrintList(reverse_head);
	cout << "Reversed linked list:" << endl;
	reverse_head = ReverseListRecursive(reverse_head);
	PrintList(reverse_head);

	ListNode *newhead;
	newhead = InversePair(head);
	cout << "Pair-reversed linked list:" << endl;
	PrintList(newhead);

	//get the original linked list
	head = InversePair(newhead);
	cout << "The Original linked list:" << endl;
	PrintList(head);

	//get the fourth last node of the linked list
	ListNode *re = RGetKthNode(head, 4);
	cout << "The 4th last node:" << endl << re->value << endl;

	//get the middle node
	re = GetMiddleNode(head);
	cout << "The middle node:" << endl << re->value << endl;

	//reverse print list
	cout << "Reverse print:" << endl;
	RPrintList(head);
	cout << endl;
	RPrintListRecursive(head);
	cout << endl;

	//destroy linked_list
	DestroyList(reverse_head);
	
	return 0;
}
