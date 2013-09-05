struct ListNode {
	int value;
	ListNode *next;
};


ListNode *build_list(ListNode *&head);
int destroy_list(ListNode *head);
void print_list(ListNode *head);

unsigned int get_list_length(ListNode *head);

ListNode *reverse_list(ListNode *head);
ListNode *reverse_list_recursive(ListNode *head);

ListNode *inverse_pair(ListNode *head);
ListNode *r_get_kth_node(ListNode *head, unsigned int k);
ListNode *get_middle_node(ListNode *head);