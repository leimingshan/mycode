#include <iostream>
#include "function.h"

using namespace std;

int main() 
{
	char x;
 
	char buf[100] ={'A','X','B','D','E','F','G','H','I','J'};
 
	BiTree<char> Test;
	Test.Create(Test.Root(),buf,1);

	cout<<"前序遍历：";
	Test.Preorder(Test.Root());
	cout<<endl;

	cout<<"中序遍历：";
	Test.Inorder(Test.Root());
	cout<<endl;
	cout<<"后续遍历：";
	Test.Postorder(Test.Root());
	cout<<endl;

	cout<<"层序遍历：";
	Test.Levelorder(Test.Root());
	cout<<endl;

	cout<<"叶子结点数为:";
	cout<<Test.LeafNodeCount(Test.Root())<<endl;
	cout<<"结点数为:";
	cout<<Test.NodeCount(Test.Root())<<endl;

	int depth=0;
	cout<<"深度为";
	cout<<Test.GetDepth(Test.Root(),depth)<<endl;
	
	cout<<"请输入指定节点:"<<endl;
	cin>>x;
	Test.GetPath(x,Test.Root());
	cout<<x<<endl<<endl;

	return 0; 
} 
