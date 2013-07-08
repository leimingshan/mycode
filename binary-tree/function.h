#include<iostream>

using namespace std;

template <class T> class Node 
{ 
    public: 
    T data;
    Node<T>* lch;
    Node<T>* rch;
    int ltag;
    int rtag;
     
    Node():lch(NULL),rch(NULL),ltag(0),rtag(0){} 
};

template <class T> class stacknode 
{ 
public: 
    Node<T> * treenode;
    int tag;
};

template <class T> class BiTree 
{ 
public: 
    Node<T> *root;
                BiTree():root(NULL){} 
    Node<T>*& Root();
                void Create(Node<T>* &R,T* buf,int i);//�������Ĵ���
    void Destroy(Node<T> *R);//������������
    void Print(T e);
    ~BiTree();
    int Search(Node<T> *R,T e,Node<T> *&p);
 
    int LeafNodeCount(Node<T> *R);//Ҷ�ӽڵ� 
    int NodeCount(Node<T> *R);//�ڵ���Ŀ
    int GetDepth(Node<T> *R,int d);//�������/
    Node<T>* GetRoot() { return Root;}  
    void GetPath(T x,Node<T>*R);//·��
    void Levelorder(Node<T> *R);//�������
    void Preorder(Node<T> *R);//ǰ�����
    void Inorder(Node<T> *R);//�������
    void Postorder(Node<T> *R);//������� 
    void Create(Node<T>* &R,T* PreBuf, int &i,T* InBuf,int b,int e);//����������
};

template <class T> class Stack { //ջ
public: 
	Stack ():Top(NULL){} 
	int IsEmpty();//�ж�ջ�Ƿ�Ϊ��
	T GetTop();//����ջ��Ԫ��
	void Push(T);//��ջ����
	T Pop();//��ջ����
	~Stack();//��������

protected: 
	struct Node { 
		T data;
		Node *next;
	};
	Node *Top;
};

template <class T> class Queue //����
{ 
public: 
    Queue();//���캯��
    int IsEmpty();//���Ƿ�Ϊ��
    void EnQueue(T);//���
    T DelQueue();//����
    T GetFront();//���Ҷ�ͷԪ��
    ~Queue();
     T data;
protected: 
    struct Node 
    { 
      T data;
      Node *next;
    };
    Node *Front;
    Node *Rear;
  
};

template <class T> Node<T>*& BiTree<T>::Root() 
{ 
	return root;
} 

//ʹ��˳��ṹ�洢�����ݽ������������� 
template <class T> void BiTree<T>::Create(Node<T> *&R,T* buf,int i) 
{ 
	if (buf[i-1]==0) 
		R = NULL;
	else 
	{ 
		R=new Node<T>;//���������
		R->data = buf[i-1];//i��ʾλ�ô�1��ʼ
		Create(R->lch, buf, 2*i);//�������������ݹ����
		Create(R->rch, buf, 2*i+1);//�������������ݹ����
	} 
} 

//���ٶ����� 
template <class T> void BiTree<T>::Destroy(Node<T> *R) 
{ 
	if(!R)
		return;

	if (R->lch)
		Destroy( R->lch);			// ���������ӣ���ɾ������
	if (R->rch)
		Destroy(R->rch);			// �������Һ��ӣ���ɾ���Һ���

	cout<<"ɾ���ڵ㣺"<< R->data<< endl;
	delete R;						// ���Һ��Ӷ�ɾ�������ɾ���ýڵ�
	R = NULL;
}

template <class T> void BiTree<T>::Print(T e) 
{ 
	cout<<e;
} 
 
template <class T> BiTree<T>::~BiTree() 
{ 
	Destroy(root);
} 
 
//��·������
template <class T> 
void BiTree<T>::GetPath(T x,Node<T>*R) 
{ 
	static int f=0,r=0;

	static bool w=false;
	static Queue<char> Queue[100];
	if(R->data!=x) 
	{ 
		if(w==false) 
			Queue[r++].data=R->data;
		if(R->lch!=NULL) 
			GetPath(x,R->lch);

		if(w==false)
			if(R->rch!=NULL) 
				GetPath(x,R->rch);

		if(w==true) {
			if(f!=r) 
				cout<<Queue[f++].data<<"->";
		}
		else 
			r--;
	} 
	else
	{ 
		cout<<"�ɸ��ڵ㵽ָ���ڵ�"<<R->data<<"��·��������:"<<r+1<<endl<<"·����:";
		w=true;
	} 
}

//��ѯ���еĽ�� 
//template <class T>    int BiTree<T>::Search(Node<T> *R,T e, Node<T> *&p) 
//{ 
//  if (R!=NULL) 
//  { 
//    if (R->data == e) { p=R;return 1;} 
//    if (Search(R->lch,e,p)) 
//      return    1;
//    else  
//      return   Search(R->rch,e,p);
//  } 
//  return 0;
//} 
//������Ҷ����� 
template <class T> int BiTree<T>::LeafNodeCount(Node<T> *R) 
{ 
	if (R==NULL) return 0;
	if ((R->lch==NULL) && (R->rch==NULL))  
	return 1;
	else 
	{ 
		int n=LeafNodeCount(R->lch); 
		int m=LeafNodeCount(R->rch);
		return m+n;//�������������������
	} 
} 
//�����Ľ������ 
template <class T> int BiTree<T>::NodeCount(Node<T> *R) 
{ 
	if (R==NULL) return 0;
	else 
	{ 
		int m=NodeCount(R->lch);
		int n=NodeCount(R->rch);
		return m+n+1;//������������������ټӸ��ڵ�
	} 
} 
//��������� 
template <class T> int BiTree<T>::GetDepth(Node<T> *R,int d) 
{ 
    if (R==NULL) return d;
    if ((R->lch==NULL) && (R->rch==NULL)) 
    return d+1;
    else 
    { 
		int m = GetDepth(R->lch,d+1);
		int n = GetDepth(R->rch,d+1);
		return n>m? n:m;//������ʹ����㷵����ȴ���Ǹ�
    } 
} 

//�ǵݹ�������� 
template <class T> void BiTree<T>::Preorder(Node<T> *R) 
{ 
	Stack<Node<T>*> S;
	while(!S.IsEmpty() || (R!=NULL)) 
	{ 
		if (R!=NULL) //������ڵ㲻�ǿ�ָ���������data�򲢽�dataֻ������ֱ�������ӱ������ٱ����Һ���
		{ 
			Print(R->data);
			S.Push(R);
			R=R->lch;
		} 
		else 
		{ 
			R=S.Pop();
			R=R->rch;
		} 
	} 
} 
//�ǵݹ�������� 
template <class T> void BiTree<T>::Inorder(Node<T> *R) 
{ 
	Stack<Node<T>*> S;
	while(!S.IsEmpty() || (R!=NULL)) 
	{ 
		if (R!=NULL)  
		{      
			S.Push(R);
			R=R->lch;
		} 
		else   
		{   
			R=S.Pop();
			Print(R->data);
			R=R->rch;   
		} 
	} 

} 
  
//�ݹ���õĺ������
template <class T> void BiTree<T>::Postorder(Node<T> *R) 
{ 
	if (R!=NULL) { 
		Postorder(R->lch);   
		Postorder(R->rch); 
		Print(R->data);                     
	} 
}

//�ݹ���ñ����������
template <class T> void BiTree<T>::Levelorder(Node<T> *R) 
{ 
	Queue<Node<T>*> Q;
	while(!Q.IsEmpty() || (R!=NULL)) 
	{ 
		if (R!=NULL) 
		{ 
			Print(R->data);
			Q.EnQueue(R->lch);
			Q.EnQueue(R->rch);
		} 
		R=Q.DelQueue();
	} 
} 
  
//������������ͺ�������������ɶ����� 
template <class T> int Stack<T>::IsEmpty() 
{ 
	if (Top==NULL) 
		return 1;
	else 
		return 0;
}
 
template <class T> T Stack<T>::GetTop() 
{ 
	if (Top==NULL)
		return T(); 
	else
		return Top->data;
}

template <class T> void Stack<T>::Push(T t) 
{ 
	Node *s=new Node;
	s->data = t;
	s->next = Top;

	Top = s;
}   
 
template <class T> T Stack<T>::Pop() 
{ 
	T t;
	if (Top==NULL)     
		cout<<"ջ�գ����"<<endl;
	else { 
		t=Top->data;
		Node *s=Top;
		Top=Top->next;
		delete s;
	} 
	return t;
}

template <class T> Stack<T>::~Stack() 
{ 
	Node *p;
	while (Top!=NULL) 
	{ 
		p=Top;
		Top=Top->next;
		delete p;
	} 
}

template <class T> Queue<T>::Queue() 
{ 
	Front = new Node;
	Front->next = NULL;
	Rear = Front;
} 

template <class T> int Queue<T>::IsEmpty() 
{ 
	if (Front==Rear) return 1;
	else    return 0;
}

template <class T> T Queue<T>::GetFront() 
{ 
	return Front==Rear? NULL:Front->data;
}

template <class T> void Queue<T>::EnQueue(T t) 
{ 
	Node *s=new Node;

	s->data = t;
	s->next=NULL;

	Rear->next = s;
	Rear = s;   
}

template <class T> T Queue<T>::DelQueue() 
{ 
	T t=NULL;
	if (Front==Rear)  
		cout<<"���пգ���Ԫ�س���!"<<endl;
	else 
	{ 
		Node *s=Front->next;
		t=s->data;
		Front->next = s->next;
		delete s;
		if (Front->next==NULL)    
			Rear=Front;
	} 
	return t;
}
 
template <class T> Queue<T>::~Queue() 
{ 
	while(Front!=Rear) 
	{ 
		cout<<DelQueue()<<endl;
	} 
}   
 
 
