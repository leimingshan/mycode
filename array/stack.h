#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

struct stack
{
	int *base;
	int *top;
	int stack_size;
};

//����һЩջ�Ĳ���
//ջ�ĳ�ʼ��
int init_stack(struct stack *s);

//��ջ����
int push(struct stack *s, int e);

//�ж�ջ�Ƿ�Ϊ��
int is_empty(struct stack *s);

//��ջ����
int pop(struct stack *s);

//����ջ��Ԫ�ص�ֵ
int get_top(struct stack *s);

//���ջ
void print_stack(struct stack *s);