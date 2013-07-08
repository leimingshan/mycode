//test for main functions of linked_list
#include <iostream>
#include "linked_list.h"

using namespace std;

int main()
{
	//build linked_list
	LinkNode *head = new LinkNode;
	head = build_list(head);
	print_list(head);
	cout << "List length:" << ' ' << get_list_length(head) << endl;
	
	LinkNode *reverse_head = reverse_list(head);
	print_list(reverse_head);
	reverse_head = reverse_list_recursive(reverse_head);
	print_list(reverse_head);
	//destroy linked_list
	destroy_list(reverse_head);
	
	return 0;
}
