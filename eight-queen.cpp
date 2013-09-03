/* n皇后问题的深度优先算法 */
#include <stack>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

#define M 20 //容许输入的最大的皇后个数

using namespace std;

struct point
{
	int x;
	int y;
};

struct node
{
	point pList[M];
	int count;
};

class myStack
{
public:
	node *base;
	node *top;
	int stack_size;

	myStack()
	{
		base = (node *)malloc(STACK_INIT_SIZE * sizeof(node));
		if (!base)
			exit(1);
		top = base;
		stack_size = STACK_INIT_SIZE;
	}

	node get_top()
	{
		node e;
		if(base != top) {
			e = *(top - 1);
			return e;
		} else {
			fprintf(stderr, "Stack is empty!\n");
			exit(1);
		}
	}

	node pop()
	{
		if(top == base) {
			fprintf(stderr, "Stack is empty.\n");
			exit(1);
		}
		else {
			top--;
			return *top;
		}
	}

	int push(node n)
	{
		if (top - base >= stack_size) {
			//栈满，追加存储空间
			base = (node *)realloc(base,
				(stack_size + STACK_INCREMENT) * sizeof(node));
			if (!base) {
				printf("Memory realloc failed!\n");
				exit(1); //存储分配失败
			}
			top = base + stack_size;
			stack_size += STACK_INCREMENT;
		}

		*top++ = n;
		return 1;
	}

	int empty()
	{
		return base == top;
	}

	int count()
	{
		return (top - base);
	}
};

int main()
{
	//stack < node > nStack;
	//stack < node > resultStack;
	myStack nStack;
	myStack resultStack;

	node tmpNode, topNode;
	int i, j, k, l;
	int queenNum;
	bool tmpBool;
	
	cout<<"Please input the queen number(<=20):";
	cin>>queenNum;
	while (queenNum > 20)
	{
		cout<<"The queen number should be < or = 20"<<endl;
		cout<<"Please input the queen number(<=20):";
		cin>>queenNum;
	}
	
	for (i = 0; i < queenNum; i++)
	{
		tmpNode.pList[0].x = i;
		tmpNode.pList[0].y = 0;
		tmpNode.count=1;
		nStack.push(tmpNode);
	}
	
	while(!nStack.empty())
	{
		//topNode = nStack.top();
		topNode = nStack.get_top();
		nStack.pop();
		if(topNode.count == queenNum)
		{
			//to-do, if satisfy then break;else continue the "while" circulation;
			resultStack.push(topNode);
		}
		else {
			for (j = 0; j < topNode.count; j++) 
				tmpNode.pList[j] = topNode.pList[j];
			for (i = 0; i < queenNum; i++)
			{
				tmpBool = false;
				for (j = 0;j < topNode.count; j++)
				if (i == topNode.pList[j].x || (topNode.pList[j].x - i)==
					(topNode.pList[j].y - topNode.count)||
					(topNode.pList[j].x - i) == (topNode.count - topNode.pList[j].y))
				{
					tmpBool = true;
					break;
				}
				if (tmpBool) 
					continue;
				tmpNode.pList[topNode.count].x = i;
				tmpNode.pList[topNode.count].y = topNode.count;
				tmpNode.count = topNode.count + 1;
				nStack.push(tmpNode);
			}
		}
	}
	
	//output all of the results to screen & file.
	char fileName[255];
	cout<<"Please input a file name (the results will write to this file):";
	cin>>fileName;
	ofstream outFile(fileName, ios::binary|ios::out);

	cout<<"Total count: "<<resultStack.count()<<endl;
	outFile<<"Total count: "<<resultStack.count()<<endl;

	while (!resultStack.empty())
	{
		//tmpNode = resultStack.top();
		tmpNode = resultStack.get_top();
		resultStack.pop();
		for (j = 0; j < queenNum - 1; j++)
		{
			cout<<"("<<tmpNode.pList[j].y + 1<<","<<tmpNode.pList[j].x + 1<<")"<<",";
			outFile<<"("<<tmpNode.pList[j].y + 1<<","<<tmpNode.pList[j].x + 1<<")"<<",";
		}
		cout<<"("<<tmpNode.pList[j].y + 1<<","<<tmpNode.pList[j].x + 1<<")"<<endl;
		outFile<<"("<<tmpNode.pList[j].y + 1<<","<<tmpNode.pList[j].x + 1<<")"<<endl;
		
		for (j = 0; j < queenNum; j++)
		{
			for (k = 0; k < tmpNode.pList[j].x; k++) {
				cout<<"_ ";
				outFile<<"_ ";
			}
			cout<<"* ";
			outFile<<"* ";
			for(k = 0; k < queenNum-tmpNode.pList[j].x - 1; k++) {
				cout<<"_ ";
				outFile<<"_ ";
			}
			cout<<endl;
			outFile<<endl;
		}
	}

	return 0;
}
