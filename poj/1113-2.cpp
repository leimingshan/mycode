#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

struct point
{
    int x,y;
    int operator < (point &b)
    {
        return ((y < b.y || (y == b.y) && (x < b.x)));
    }
}ptmp;

#define pi 3.1415926
double sqr(double a) 
{
       return ((a) * (a));
}
double dis2(point a,point b) 
{
       return (sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)));
}
#define multi(a,b,c) ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x))


int cmp(const void *a,const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    point e,f;
    e = *c;
    f = *d;
    int t = multi(ptmp,e,f);
    if(t > 0)
        return -1;
    if(t == 0 && dis2(ptmp,e) <= dis2(ptmp,f))
        return -1;
    return 1;
}
void GrahamScanGram(point p[],int stack[],int &top,int n)
{
     int u = 0,i;
     for(i = 0; i < n; i++)
         if(p[i] < p[u]) u = i;
     ptmp = p[0];
     p[0] = p[u];
     p[u] = ptmp;    
     ptmp = p[0];
     
     qsort(p+1,n-1,sizeof(p[0]),cmp);
     
     stack[0] = 0;
     stack[1] = 1;
     stack[2] = 2;
     top = 3;
     for(i = 3; i < n; i++)
     {
           while(top >= 2 && multi(p[stack[top - 2]],p[stack[top-1]],p[i]) <= 0)
               top--;
           stack[top++] = i;
     }
}
int main()
{
    point p[1003];
    int stack[1003],top;
    int n,l,i;
    double l1;
    while(cin >> n >> l)
    {
        for(i = 0; i < n; i++)
            cin >> p[i].x >> p[i].y;
        GrahamScanGram(p,stack,top,n);
        double g = 0;
		
		for(int i=0;i<top;i++) {
			cout<<p[stack[i]].x<<' '<<p[stack[i]].y<<endl;
		}
		
        for(i = 0; i < top-1; i++)
            g += dis2(p[stack[i]],p[stack[i+1]]);
        l1 = 2*pi*l + dis2(p[stack[i]],p[stack[0]]);
        printf("%.0lf\n",g+l1);
    }
    return 0;
}
