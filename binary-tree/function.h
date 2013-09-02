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
    void Create(Node<T>* &R,T* buf,int i);//二叉树的创建
    void Destroy(Node<T> *R);//二叉树的销毁
    void Print(T e);
    ~BiTree();
    int Search(Node<T> *R,T e,Node<T> *&p);
 
    int LeafNodeCount(Node<T> *R);//叶子节点 
    int NodeCount(Node<T> *R);//节点数目
    int GetDepth(Node<T> *R,int d);//树的深度/
    Node<T>* GetRoot() { return Root;}  
    void GetPath(T x,Node<T>*R);//路径
    void Levelorder(Node<T> *R);//层序遍历
    void Preorder(Node<T> *R);//前序遍历
    void Inorder(Node<T> *R);//中序遍历
    void Postorder(Node<T> *R);//后序遍历 
    void Create(Node<T>* &R,T* PreBuf, int &i,T* InBuf,int b,int e);//创建二叉树
};

template <class T> class Stack { //栈
public: 
	Stack ():Top(NULL){} 
	int IsEmpty();//判断栈是否为空
	T GetTop();//查找栈顶元素
	void Push(T);//入栈操作
	T Pop();//出栈操作
	~Stack();//析构函数

protected: 
	struct Node { 
		T data;
		Node *next;
	};
	Node *Top;
};

template <class T> class Queue //队列
{ 
public: 
    Queue();//构造函数
    int IsEmpty();//判是否为空
    void EnQueue(T);//入队
    T DelQueue();//出队
    T GetFront();//查找对头元素
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

//使用顺序结构存储的数据建立二叉链表树 
template <class T> void BiTree<T>::Create(Node<T> *&R,T* buf,int i) 
{ 
	if (buf[i-1]==0) 
		R = NULL;
	else 
	{ 
		R=new Node<T>;//创建根结点
		R->data = buf[i-1];//i表示位置从1开始
		Create(R->lch, buf, 2*i);//创建左子树，递归调用
		Create(R->rch, buf, 2*i+1);//创建右子树，递归调用
	} 
} 

//销毁二叉树 
template <class T> void BiTree<T>::Destroy(Node<T> *R) 
{ 
	if(!R)
		return;

	if (R->lch)
		Destroy( R->lch);			// 若存在左孩子，先删除左孩子
	if (R->rch)
		Destroy(R->rch);			// 若存在右孩子，先删除右孩子

	cout<<"删除节点："<< R->data<< endl;
	delete R;						// 左右孩子都删除后，最后删除该节点
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
 
//求路径长度
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
		cout<<"由根节点到指定节点"<<R->data<<"的路径长度是:"<<r+1<<endl<<"路径是:";
		w=true;
	} 
}

//查询树中的结点 
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
//求树的叶结点数 
template <class T> int BiTree<T>::LeafNodeCount(Node<T> *R) 
{ 
	if (R==NULL) return 0;
	if ((R->lch==NULL) && (R->rch==NULL))  
	return 1;
	else 
	{ 
		int n=LeafNodeCount(R->lch); 
		int m=LeafNodeCount(R->rch);
		return m+n;//左子树结点加右子树结点
	} 
} 
//求树的结点总数 
template <class T> int BiTree<T>::NodeCount(Node<T> *R) 
{ 
	if (R==NULL) return 0;
	else 
	{ 
		int m=NodeCount(R->lch);
		int n=NodeCount(R->rch);
		return m+n+1;//左子树加右子树结点再加根节点
	} 
} 
//求树的深度 
template <class T> int BiTree<T>::GetDepth(Node<T> *R,int d) 
{ 
    if (R==NULL) return d;
    if ((R->lch==NULL) && (R->rch==NULL)) 
    return d+1;
    else 
    { 
		int m = GetDepth(R->lch,d+1);
		int n = GetDepth(R->rch,d+1);
		return n>m? n:m;//从左算和从右算返回深度大的那个
    } 
} 

//非递归先序遍历 
template <class T> void BiTree<T>::Preorder(Node<T> *R) 
{ 
	Stack<Node<T>*> S;
	while(!S.IsEmpty() || (R!=NULL)) 
	{ 
		if (R!=NULL) //如果根节点不是空指针则输出其data域并将data只想左孩子直到将左孩子遍历完再遍历右孩子
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
//非递归中序遍历 
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
  
//递归调用的后序遍历
template <class T> void BiTree<T>::Postorder(Node<T> *R) 
{ 
	if (R!=NULL) { 
		Postorder(R->lch);   
		Postorder(R->rch); 
		Print(R->data);                     
	} 
}

//递归调用遍历层序遍历
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
  
//利用先序遍历和后序遍历序列生成二叉树 
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
		cout<<"栈空，溢出"<<endl;
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
		cout<<"队列空，无元素出队!"<<endl;
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
 
 
