#include <stdlib.h>
#include <stdio.h>
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
#define N 10

struct seat
{
	int x;
	int y;
};//当前访问的坐标

struct finds
{
	int ord;
	struct seat s;
	int di;
};//di为下个寻找的方向

struct stack
{
	struct finds *base;
	struct finds *top;
	int size;
};

void init_stack(struct stack *s)
{
	s->base = s->top = (struct finds *)malloc(STACK_INIT_SIZE * sizeof(struct finds));
	s->size = STACK_INIT_SIZE;
}//堆栈初始化

void push(struct stack *s, struct finds *find)
{
	struct finds *link, *end;
	if(s->top - s->base >= s->size)
	{
		s->base = (struct finds *)realloc(s->base, (s->size+STACK_INIT_SIZE) * sizeof(struct finds));
		
		s->top = s->base + s->size;
		s->size += STACK_INIT_SIZE;
	}
	s->top->ord = find->ord;
	s->top->s.x = find->s.x;
	s->top->s.y = find->s.y;
	s->top->di = find->di;
	s->top++;
}

void pop(struct stack *s, struct finds *find)
{
	s->top--;
	find->ord = s->top->ord;
	find->s.x = s->top->s.x;
	find->s.y = s->top->s.y;
	find->di = s->top->di;
}

void footprint(int a[N][N], struct seat *seat)
{
	int i,j;
	i = seat->x;
	j = seat->y;
	a[i][j] = -1;
}

void nextpos(struct seat *find, struct seat *seat, int di)
{
	int i, j;
	switch(di) {
	case 1:
		i = seat->x;
		j = seat->y + 1;
		break;
	case 2:
		i = seat->x + 1;
		j = seat->y;
		break;
	case 3:
		i = seat->x;
		j = seat->y - 1;
		break;
	case 4:
		i = seat->x - 1;
		j = seat->y;
		break;
	}
	
	find->x = i;
	find->y = j;
}

int pass(struct seat *curpos, int a[N][N])
{
	int i, j;
	i = curpos->x;
	j = curpos->y;
	
	if(a[i][j] == 0)
		return 1;
	else 
		return 0;
}

void print_stack(struct stack *s)
{
	struct finds *p;
	if (s->base == s->top)
		return;
	p = s->base;
	do {
		printf("(%d %d)->", p->s.x, p->s.y);
		p++;
	} while (p != s->top);
}

int main()
{
	struct stack *s;
	struct finds *find, *e;
	struct seat *start, *end, *curpos;
	int curstep = 1, i, j, n, m, pa;
	
	int a[N][N]  =  {{1,1,1,1,1,1,1,1,1,1},
				   {1,0,0,1,0,0,0,1,0,1},
				   {1,0,0,1,0,0,0,1,0,1},
				   {1,0,0,0,0,1,1,0,0,1},
				   {1,0,1,1,1,0,0,0,0,1},
				   {1,0,0,0,1,0,0,0,0,1},
				   {1,0,1,0,0,0,1,0,0,1},
				   {1,0,1,1,1,0,1,1,0,1},
				   {1,1,0,0,0,0,0,0,0,1},
				   {1,1,1,1,1,1,1,1,1,1}};
				  
	s = (struct stack *)malloc(sizeof(struct stack));
	find = (struct finds *)malloc(sizeof(struct finds));
	e = (struct finds *)malloc(sizeof(struct finds));
	start = (struct seat *)malloc(sizeof(struct seat));
	end = (struct seat *)malloc(sizeof(struct seat));
	curpos = (struct seat *)malloc(sizeof(struct seat));
	init_stack(s);

	while(1)
	{
		printf("进入迷宫的位置 (n m):\n");
		scanf("%d %d", &curpos->x, &curpos->y);
		if(curpos->x <= 0 || curpos->y <= 0 || curpos->x >= N || curpos->y >= N)
			puts("输入数据错误,请重新输入");
		else 
			break;
	}
	while(1)
	{
		printf("走出迷宫的位置 (n m):\n");
		scanf("%d %d", &end->x, &end->y);
		if(end->x <= 0 || end->y <= 0 || end->x >= N || end->y >= N)
			puts("输入数据错误,请重新输入");
		else 
			break;
	}

	do
	{
		if(pass(curpos,a))
		{
			footprint(a,curpos);
			e->ord = curstep;
			e->s.x = curpos->x;
			e->s.y = curpos->y;
			e->di = 1;
			push(s, e);
			if(curpos->x == end->x && curpos->y == end->y)
				break;
			nextpos(curpos, &e->s, 1);
			curstep++;
		} 
		else   {
			if(e->di < 4) {
				pop(s, e);
				e->di++;
				push(s, e);
				nextpos(curpos, &e->s, e->di);
			}
			else if(e->di == 4)
			{
				pop(s, e);
				pop(s, e);
				push(s, e);
				e->di++;
				if(e->di > 4)
					pop(s, e);
				nextpos(curpos, &e->s, e->di);
			}
		}
	}while(1);
	
	puts("输出路径为:");
	print_stack(s);
	puts("EXIT");

	return 0;
}