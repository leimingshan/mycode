#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

static struct stack s1;
static struct stack *s = &s1;

//判断是否是操作符
int is_operator(int c)
{
	if ('+' == c || '-' == c || '*' == c || '/' == c || '(' == c || ')' == c)
		return 1;
	return 0;
}

//比较运算符的优先级
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

//利用栈，转换中缀表达式到后缀表达式 
int infix_to_postfix(int *infix, int *postfix, int size)
{
	int i, k, temp;
	for (i = 0,k = 0;i < size; i++) {
		if (is_operator(infix[i])) {//遇到运算符了
			if (')' == infix[i]) {//遇到右括号
				//弹出在栈中的所有元素
				while(!is_empty(s)) {
					if('(' == (temp = pop(s)))//遇到左括号停止输出
						break;
					else
						postfix[k++] = temp;
				}
			}
			else {
				if ('(' == infix[i]) //遇到左括号
					push(s, infix[i]);
				
				else {//处理普通运算符
					if (is_empty(s))//栈空就直接压入栈
						push(s, infix[i]);
					else {
						while (!is_empty(s)) {
							if(cmp_operator(temp = get_top(s), infix[i]) >= 0) { //如果这里是top操作 不是pop 如果是后者要记得再执行一个push
								pop(s); //将这个字符弹出 切记
								postfix[k++] = temp;
							}
							else{
								//push(temp); //这里压回去 为什么我上面使用top会使程序出错 因为那里会成为一个死循环 必须要将其弹出
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

//计算后缀表达式的值
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
