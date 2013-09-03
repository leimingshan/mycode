struct LinkNode {
	int value;
	LinkNode *next;
};


LinkNode *build_list(LinkNode *&head);
int destroy_list(LinkNode *head);
void print_list(LinkNode *head);

unsigned int get_list_length(LinkNode *head);
LinkNode *reverse_list(LinkNode *head);
LinkNode *reverse_list_recursive(LinkNode *head);

LinkNode *inverse_pair(LinkNode *head);
