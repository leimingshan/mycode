struct ListNode {
	int value;
	ListNode *next;
};


ListNode *BuildList(ListNode *&head);
int DestroyList(ListNode *head);
void PrintList(ListNode *head);

unsigned int GetListLength(ListNode *head);

ListNode *ReverseList(ListNode *head);
ListNode *ReverseListRecursive(ListNode *head);

ListNode *InversePair(ListNode *head);
ListNode *RGetKthNode(ListNode *head, unsigned int k);
ListNode *GetMiddleNode(ListNode *head);

void RPrintList(ListNode *head);
void RPrintListRecursive(ListNode *head);

bool HasCircle(ListNode *head);
ListNode *GetFirstCommonNode(ListNode *head);
ListNode *GetFirstNodeInCircle(ListNode *head);

bool IsIntersected(ListNode * head1, ListNode * head2);