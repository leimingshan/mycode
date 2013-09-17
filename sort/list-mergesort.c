// Linked list mergesort
// 链表排序中使用归并排序：归并排序不仅保持了它的 O( nlog(n) ) 的时间复杂度，
// 而且它在数组排序中广受诟病的空间复杂度，在链表排序中从 O(n) 降低到 O( log(n) )。

// 对于单向链表的二路归并排序，首先是要找到链表的中间节点，将链表等分。
// 我们可以使用快慢指针的方式找到链表的中间节点，即一个指针以一个步长移动，另一个指针使用两个步长移动，
// 当快指针到结尾位置时，慢指针正好在中间位置。接下来是对两个链表进行归并排序。

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NODE_NUM 20

struct ListNode {
    int value;
    struct ListNode *next;
};

/*
 *创建一个带头结点的单向链表
 *@parm[in]: count 链表节点个数
 *@return : 链表头结点 
 */
struct ListNode *BuildList(int count)
{
    if (count <= 0) {
        printf("Could not create LinkedList! The input count %d should be bigger than 0!\n", count);
        return NULL;
    }
    struct ListNode *head = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (NULL == head) {
        printf("Malloc failed!\n");
        exit(1);
    }

    struct ListNode *current = head;
    srand(time(0));
    head->value = rand() % 100;

    for (int i = 0; i < count; i++) {
        struct ListNode *temp = (struct ListNode *)malloc(sizeof(struct ListNode));
        temp->value = rand() % 100;
        current->next = temp;
        current = current->next;
    }
    current->next = NULL;
    return head;
}

/*
 *打印输出链表
 *@para[in]: head 有序链表首地址指针 
 */
void PrintList(struct ListNode *head)
{
    struct ListNode *node = head;
    while (node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

/*
 *释放链表空间
 *@para[in]: head 有序链表首地址指针 
 */
int DestroyList(struct ListNode *head)
{
    struct ListNode *p;
    if (head == NULL)
        return -1;

    while (head != NULL) {
        p = head->next;
        free(head);
        head = p;
    }
    return 0;
}

/*
 * 按递增顺序,将两个有序单向链表，归并成一个有序单向链表
 * @para[in]: head1  有序单向链表首地址指针
 * @para[in]: head2 有序单向链表首地址指针
 * @return:   返回排好序后的链表首地址指针
 */
struct ListNode *merge(struct ListNode *head1, struct ListNode *head2)
{
    if (NULL == head1)
        return head2;
    if (NULL == head2)
        return head1;

    struct ListNode *merged_head;
    if (head1->value < head2->value) {
        merged_head = head1;
        head1 = head1->next;
    } else {
        merged_head = head2;
        head2 = head2->next;
    }
    merged_head->next = merge(head1, head2);
    return merged_head;
}

/*
 *使用快慢指针，等分单向链表,并调用merge函数对链表排序
 *@para[in/out]: head有序单向链表首地址指针
 *@return: 返回排好序的单链表首地址地址
 */
struct ListNode *MergeSort(struct ListNode *head)
{
    struct ListNode *first = head;
    struct ListNode *second = head;

    if (NULL == head) {
        return NULL;
    }
    
    //只剩一个节点时，返回
    if (head->next == NULL) {
        return head;
    }

    //使用快慢指针将链表等分为两个链表
    while (second->next != NULL && second->next->next != NULL) {
        first = first->next;
        second = second->next->next;
    }
    if (first->next != NULL) {
        second = first->next;
        first->next = NULL;
        first = head;
    }

    return merge(MergeSort(first), MergeSort(second));
}

int main()
{
    struct  ListNode *head = BuildList(NODE_NUM);
    printf("Before Sort:\n");
    PrintList(head);

    struct ListNode *merged_head = MergeSort(head);
    printf("After Sort:\n");
    PrintList(merged_head);

    DestroyList(merged_head);

    return 0;
}
