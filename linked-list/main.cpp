//Test for main functions of linked_list
#include <iostream>
#include "linked_list.h"

using namespace std;

int main()
{
	//build linked_list
	ListNode *head = new ListNode;
	head = build_list(head);

	cout << "Original linked list:" << endl;
	print_list(head);

	cout << "List length:" << endl << get_list_length(head) << endl;
	
	ListNode *reverse_head = reverse_list(head);
	cout << "Reversed linked list:" << endl;
	print_list(reverse_head);
	cout << "Reversed linked list:" << endl;
	reverse_head = reverse_list_recursive(reverse_head);
	print_list(reverse_head);

	ListNode *newhead;
	newhead = inverse_pair(head);
	cout << "Pair-reversed linked list:" << endl;
	print_list(newhead);

	//get the original linked list
	head = inverse_pair(newhead);
	cout << "The Original linked list:" << endl;
	print_list(head);

	//get the fourth last node of the linked list
	ListNode *re = r_get_kth_node(head, 4);
	cout << "The 4th last node:" << endl << re->value << endl;

	//get the middle node
	re = get_middle_node(head);
	cout << "The middle node:" << endl << re->value << endl;
	//destroy linked_list
	destroy_list(reverse_head);
	
	return 0;
}
