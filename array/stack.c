#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int init_stack(struct stack *s)
{
	s->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
	if (!s->base)
		exit(1);
	s->top = s->base;
	s->stack_size = STACK_INIT_SIZE;
	return 1;
}

int push(struct stack *s, int e)
{
	if (s->top - s->base >= s->stack_size) {
		//Õ»Âú£¬×·¼Ó´æ´¢¿Õ¼ä
		s->base = (int *)realloc(s->base,
			(s->stack_size + STACK_INCREMENT) * sizeof(int));
		if (!s->base) {
			printf("Memory realloc failed!\n");
			exit(1); //´æ´¢·ÖÅäÊ§°Ü
		}
		s->top = s->base + s->stack_size;
		s->stack_size += STACK_INCREMENT;
	}

	*s->top++ = e;
	return 1;
}

int is_empty(struct stack *s)
{
	return s->base == s->top;
}

int pop(struct stack *s)
{
	if(is_empty(s)) {
		fprintf(stderr, "Stack is empty.\n");
		exit(1);
	}
	else {
		s->top--;
		return *s->top;
	}
}

int get_top(struct stack *s)
{
	int e;
	if(!is_empty(s)) {
		e = *(s->top - 1);
		return e;
	} else {
		fprintf(stderr, "Stack is empty!\n");
		exit(1);
	}
}

void print_stack(struct stack *s)
{
	int *p;
	if (is_empty(s))
		return;
	p = s->base;
	do {
		printf("%d ", *p);
		p++;
	} while (p != s->top);
}
