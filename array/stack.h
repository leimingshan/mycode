#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

struct stack
{
	int *base;
	int *top;
	int stack_size;
};

//定义一些栈的操作
//栈的初始化
int init_stack(struct stack *s);

//入栈操作
int push(struct stack *s, int e);

//判断栈是否为空
int is_empty(struct stack *s);

//出栈操作
int pop(struct stack *s);

//返回栈定元素的值
int get_top(struct stack *s);

//输出栈
void print_stack(struct stack *s);