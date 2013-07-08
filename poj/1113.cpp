#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iomanip>

#define MAXN 101

using namespace std;

const double pi = 3.141592654;

struct point
{
	int x;
	int y;
};

point *p;

int max(int a,int b)
{
	return a>b?a:b;
}

int dis(point p1,point p2)//两点的距离的平方
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

//叉积，结果小于0表示向量p0p1的极角大于p0p2的极角，等于则两向量共线
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

int main()
{
	int N, L;
	while(cin>>N>>L)
	{
		p = new point[N+10];
		point* stack = new point[N+10];
		int sum = 0;
		for(int i=0;i<N;i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		
		int top = Graham_scan(p,stack,N);
		  
        double minlen=0;  
        for(int i=0;i<top;i++)
            minlen += sqrt((double)dis(stack[i], stack[(i+1) % top]));	
        minlen += 2*pi*L;  
		cout<<fixed<<setprecision(0)<<minlen<<endl;  
		
		delete p;
		delete stack;
	}
	return 0;
}
