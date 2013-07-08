#include <iostream>

using namespace std;

class Node {
	public:
	int data;
	Node *next;
};

int main()
{

	Node *head = new Node;         //确定头结点 
	Node *p = head;
	Node *q = p;
	int s = 1;
	int n, k, m;
	
	cout<<"Please input n:"; 
	cin>>n;  
	if (n < 1)                 //考虑n输入错误的情况 
	    cout<<"n ERROR"<<endl;  
	
	cout<<"k:";  
	cin>>k;  
	if (k < 1 || k > n)                 //考虑k输入异常的情况 
	{   cout<<"k值输入错误"<<endl;  } 
	
	//cout<<"请输入m值:"; 
	cout<<"m:";
	cin>>m; 
	if (m < 1)                     //考虑m输入异常的情况 
	    cout<<"m值输入错误"<<endl;
		

	for (int i = 1; i < n; i++)                         //赋初值 
	{  
		p->data = i;  
		p->next = new Node;           //为下一个新建内存  
		p = p->next; 
	}

	p->data = n;                              //最后一个单独处理 
	p->next = head;                        //指向头，形成循环链表 
	p = head;
	
	for (int i = 1; i < k; i++)
		p = p->next;
	
	while (p != p->next)         
	{   
		for (int i = 1; i < m-1; i++)         //查找q的节点     
			p = p->next;                
		q = p->next;
		
		cout<<"第"<<s<<"个出环的人编号是："<<q->data<<endl;
		cout<<s<<"---"<<q->data<<endl;
		
		p->next = q->next; 
		p = p->next;
		delete q;
		s++;
	}

	cout<<"The lase one is"<<p->data<<endl;
	delete p;

	return 0;		
}
