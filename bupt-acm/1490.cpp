#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define MAXN 120

using namespace std;

struct point
{
	int x;
	int y;
} p[MAXN], stack[MAXN];

int dis(point p1,point p2)//两点的距离的平方
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

int multi(point p1, point p2, point p0)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

int cmp(point a,point b)
{
	int temp = multi(a,b,p[0]);
	if(temp>0)
		return 1;
	else if(temp==0&&dis(a,p[0])<dis(b,p[0]))
		return 1;
	return 0;
}

//Graham_scan
//返回凸包点数
int Graham_scan(point p[], point stack[], const int n)
{
	int i,j;
	int k=0;
	int len, top=1;
	point temp;
	//寻找最下且偏左的点
	for(i=1;i<n;i++)
		if(p[i].y<p[k].y||((p[i].y==p[k].y)&&(p[i].x<p[k].x)))
			k=i;
	
	temp=p[0];
	p[0]=p[k];
	p[k]=temp;

	sort(p+1,p+n,cmp);
	
	stack[0]=p[0];
	stack[1]=p[1];
	stack[2]=p[2];
	top = 3;
	for(i=3;i<n;i++)
	{
		while(top >= 2 && multi(stack[top-1], p[i], stack[top-2]) <= 0)
			top--;
	
		stack[top++]=p[i];
	}

	return top;
}

double Area(point *p, int nv)
{
    if (nv < 3) return 0;
    int i;
    double ret = 0;
    for (i = 2; i < nv; i++)
    {
        ret += multi(p[i-1], p[i], p[0]) / 2.0;
    }
    return ret;
}

int main()
{
	int N;
	while(scanf("%d",&N)!=EOF)
	{
		int sum = 0;
		int base = 0;
		for(int i=0;i<N;i++)
			scanf("%d %d", &p[i].x, &p[i].y);

		int top = Graham_scan(p,stack,N);
		
		
		printf("%.1f\n", Area(stack, top));
	}
	return 0;
}
