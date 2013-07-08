#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static struct stack s1;
static struct stack *s = &s1;

//�ж��Ƿ��ǲ�����
int is_operator(int c)
{
	if ('+' == c || '-' == c || '*' == c || '/' == c || '(' == c || ')' == c)
		return 1;
	return 0;
}

//�Ƚ�����������ȼ�
int cmp_operator(int o1,int o2)
{
	int value_postfix1,value_postfix2;
	value_postfix1 = value_postfix2 = 0;
	if ('+' == o1 || '-' == o1)
		value_postfix1 = 1;
	else
		if ('/' == o1 || '*' == o1)
			value_postfix1 = 2;
	if ('+' == o2 || '-' == o2)
		value_postfix2 = 1;
	else
		if ('/' == o2 || '*' == o2)
			value_postfix2 = 2;
	return value_postfix1 - value_postfix2;
}

//����ջ��ת����׺���ʽ����׺���ʽ 
int infix_to_postfix(int *infix, int *postfix, int size)
{
	int i, k, temp;
	for (i = 0,k = 0;i < size; i++) {
		if (is_operator(infix[i])) {//�����������
			if (')' == infix[i]) {//����������
				//������ջ�е�����Ԫ��
				while(!is_empty(s)) {
					if('(' == (temp = pop(s)))//����������ֹͣ���
						break;
					else
						postfix[k++] = temp;
				}
			}
			else {
				if ('(' == infix[i]) //����������
					push(s, infix[i]);
				
				else {//������ͨ�����
					if (is_empty(s))//ջ�վ�ֱ��ѹ��ջ
						push(s, infix[i]);
					else {
						while (!is_empty(s)) {
							if(cmp_operator(temp = get_top(s), infix[i]) >= 0) { //���������top���� ����pop ����Ǻ���Ҫ�ǵ���ִ��һ��push
								pop(s); //������ַ����� �м�
								postfix[k++] = temp;
							}
							else{
								//push(temp); //����ѹ��ȥ Ϊʲô������ʹ��top��ʹ������� ��Ϊ������Ϊһ����ѭ�� ����Ҫ���䵯��
								break;
							}
						}
						push(s, infix[i]);
					}
				}
			}
		}
		else
			postfix[k++] = infix[i];
	}
	while (!is_empty(s))
		postfix[k++] = pop(s);
	return k;
}

//�����׺���ʽ��ֵ
int value_postfix(int *expression,int size)
{
	int number1, number2;
	int i;

	for (i = 0; i < size; i++){
		if (is_operator(expression[i])) {

			if (!is_empty(s))
				number1 = pop(s);
			if (!is_empty(s))
				number2 = pop(s);

			switch ((int)expression[i]) {
			case '+':
				push(s, number1 + number2);
				break;
			case '-':
				push(s, number2 - number1);
				break;
			case '*':
				push(s, number1 * number2);
				break;
			case '/':
				if (number2)
					push(s, number1 / number2);
				else {
					fprintf(stderr, "divisor is 0!!!\n");
					exit(1);
				}
				break;
			}
		}
		else
			push(s, expression[i]);
	}

	if (!is_empty(s))
		return pop(s);
	else
		return 1;
}

int main()
{
	int in[1024];
	int out[1024];
	
	char in_buf[1024];
	int in_size, i, k;

	printf("Please input infix expression:\n");
	gets(in_buf);

	for (i = 0; i < strlen(in_buf); i++)
		in[i] = in_buf[i];

	init_stack(s);

	k = infix_to_postfix(in, out, strlen(in_buf));

	printf("\nThe Postfix expression is:\n");
	for (i = 0; i < k; i++)
		printf("%c", out[i]);
	printf("\n\n");

	for (i = 0; i < k; i++) {
		if (out[i] >= '1' && out[i] <= '9')
			out[i] += 1 - '1';
		else if (!is_operator(out[i])) {
			printf("Input %c = ", out[i]);
			scanf("%d", &out[i]);
		}
	}
	
	printf("\nValue Of Expression = %d\n", value_postfix(out, k));

	return 0;
}
