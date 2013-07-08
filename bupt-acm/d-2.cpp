#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define MAXN 101

using namespace std;

int top;//͹���Ķ������

struct point
{
	int x;
	int y;
} p[MAXN],stack[MAXN];

int max(int a,int b)
{
	return a>b?a:b;
}

int dis(point p1,point p2)//����ľ����ƽ��
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

//��������С�ڱ�ʾ����p0p1�ļ��Ǵ���p0p2�ļ��ǣ�����������������
int multi(point p1, point p2, point p0)
{
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

int cmp(point a,point b)
{
	if(multi(a,b,p[0])>0)
		return 1;
	if(multi(a,b,p[0])==0&&dis(a,p[0])<dis(b,p[0]))
		return 1;
	return 0;
}

//Graham_scan
void Graham_scan(point p[],point stack[],int n)
{
	int i,j,k=0;
	top=2;
	point temp;
	//Ѱ��������ƫ��ĵ�
	for(i=1;i<n;i++)
		if(p[i].y<p[k].y||((p[i].y==p[k].y)&&(p[i].x<p[k].x)))
		k=i;
	
	temp=p[0];
	p[0]=p[k];
	p[k]=temp;

	sort(p+1,p+n,cmp);
}



int main()
{
	int N;
	while(scanf("%d",&N)!=EOF)
	{
		int sum = 0;
		for(int i=0;i<N;i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		
		Graham_scan(p,stack,N);
		
		//for(int i= 0;i<N;i++)
			//printf("%d %d\n", p[i].x, p[i].y);
		//�������
		for(int i=0;i<N-1;i++)
		{
			sum += p[i].x * p[i+1].y - p[i+1].x*p[i].y;
		}
		sum += p[N-1].x*p[0].y-p[0].x*p[N-1].y;
		
		double result = abs(sum) / 2.0;
		printf("%.1f\n", result);
	}
	return 0;
}
