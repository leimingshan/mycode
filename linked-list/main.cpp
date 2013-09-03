//Test for main functions of linked_list
#include <iostream>
#include "linked_list.h"

using namespace std;

int main()
{
	//build linked_list
	LinkNode *head = new LinkNode;
	head = build_list(head);

	cout << "Original linked list:" << endl;
	print_list(head);

	cout << "List length:" << endl << get_list_length(head) << endl;
	
	LinkNode *reverse_head = reverse_list(head);
	cout << "Reversed linked list:" << endl;
	print_list(reverse_head);
	cout << "Reversed linked list:" << endl;
	reverse_head = reverse_list_recursive(reverse_head);
	print_list(reverse_head);

	LinkNode *newhead;
	newhead = inverse_pair(head);
	cout << "Pair-reversed linked list:" << endl;
	print_list(newhead);

	//destroy linked_list
	destroy_list(reverse_head);
	
	return 0;
}
