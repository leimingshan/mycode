#Linked list
####In computer science, a linked list is a data structure consisting of a group of nodes which together represent a sequence. Under the simplest form, each node is composed of a data and a reference (in other words, a link) to the next node in the sequence.
####This structure allows for efficient insertion or removal of elements from any position in the sequence.

#链表
####在计算机科学中，链表作为一种基础的数据结构可以用来生成其它类型的数据结构。链表通常由一连串节点组成，每个节点包含任意的实例数据（data fields）和一或两个用来指向明上一个/或下一个节点的位置的链接（"links"）。
####链表最明显的好处就是，链表允许插入和移除表上任意位置上的节点，链表在插入的时候可以达到O(1)的复杂度，比另一种线性表快得多，但是查找一个节点或者访问特定编号的节点则需要O(n)的时间，而顺序表相应的时间复杂度分别是O(logn)和O(1)。链表不允许随机存取。
####链表有很多种不同的类型：单向链表，双向链表以及循环链表。

*****************
链表的操作大多需要注意非NULL指针的判断，以及next指针的操作，另外，要注意链表在插入与删除时与线性表区别的特点。这里主要讨论的是单链表的操作。

####函数功能列表：

1. 求单链表中结点的个数
2. 将单链表反转
3. 查找单链表中的倒数第K个结点（k > 0）
4. 查找单链表的中间结点
5. 从尾到头打印单链表
6. 已知两个单链表 head1 和 head2 各自有序，把它们合并成一个链表依然有序
7. 判断一个单链表中是否有环
8. 判断两个单链表是否相交
9. 求两个单链表相交的第一个节点
10. 已知一个单链表中存在环，求进入环中的第一个节点
11. 给出一单链表头指针head和一节点指针deleted，O(1)时间复杂度删除节点deleted
